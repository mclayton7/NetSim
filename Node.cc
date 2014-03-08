// Definition of Node class
// ECE8893, Final Project, Fall 2012

/****** Description **************************************
 The Node object represents a single network node, either an end sysem or a router (it turns out the needed functionality is identical in either case). The Node object maintains a list of associated NetworkInterface objects, a list of associated Application objects, and a representation of the node’s address. We will use a simple 32–bit integer for node addressing. It must implement a Send and a Receive function to model sending and receiving packets. It must implement AddNeighbor function to add another network interface and a point to point link to construct the topology. Nodes also need a routing table, discussed later
 *********************************************************/

// Node 1, 2, 3, 4, ... , n
#include <iostream>
#include <cstdlib>
#include "Node.h"
#include "NetworkInterface.h"
#include "DropTailQueue.h"
#include "Application.h"
#include "NetworkLink.h"
#include "Simulator.h"
#include "myBFS.h"

using namespace std;


// Typesafe Templated Event Handlers:
// Event0
template <typename T, typename OBJ>
void Event0<T, OBJ>::CallHandler()
{
    (obj->*handler)();
}
// Event1
template <typename T, typename OBJ, typename U1, typename T1>
void Event1<T, OBJ, U1, T1>::CallHandler()
{
    (obj->*handler)(t1);
}



// Constructors
// Default Constructor
int Node::count = 0;
Node::Node()
  : address(Node::count++), interfaces(0), applications(0), nextHopRoutes(0),
    pktsSent(0), pktsReceived(0), bytesSent(0), bytesReceived(0), pktsDropped(0)
{
    // Nothing to do
}


// Member Functions
// Populate Routing Table
void Node::ComputeRoutes()
{
	// Breadth First Search (god routing)
    myBFS(this);
    makingTable(this);
}

// Add a new interface, p2p link and neighbor node
void Node::AddNeighbor(Node* node, bool highspeed)
{
    // Create Network Interface for here (hNet) and there (tNet):
    NetworkInterface* hNet = new NetworkInterface();
    NetworkInterface* tNet = new NetworkInterface();
    
    // Create P2P links:
    NetworkLink* hLink;
    NetworkLink* tLink;
    if(highspeed)   // If the connection is a highspeed link:
    {
        hLink = new NetworkLink(10, 100000000); // 10ms delay
        tLink = new NetworkLink(10, 100000000); // 100Mbit/s speed
    }
    else            // If the connection is a regular link:
    {
        hLink = new NetworkLink();
        tLink = new NetworkLink();
    }
    
    // Connect/Setup the two links:
    hLink->peerNode = node;
    hLink->peerInterface = tNet;
    tLink->peerNode = this;
    tLink->peerInterface = hNet;
    
    // Connect/Setup the two Interfaces:
    hNet->AddP2PLink(hLink);
    hNet->node = this;
    tNet->AddP2PLink(tLink);
    tNet->node = node;
    
    // Add Interfaces to Nodes:
    this->interfaces.push_back(hNet);
    node->interfaces.push_back(tNet);
}

// Add Application to node
void Node::AddApplication(Application* app)
{
    app->node = this;
	applications.push_back(app);
}

// Send count bytes to specified destination
void Node::Send(Packet* pkt)
{
    // Call NetworkInterface::Send to send packet
    if(!interfaces.empty())
    {
        // Routing Table Lookup:
        if(pkt->destination == address)
        {
            PacketArrival(pkt);
        }
        else
        {
            // Schedule Send (include Processing Delay)
            Time_t processingDelay = 0;
            Simulator::Schedule(processingDelay,
                                &NetworkInterface::Send,
                                interfaces[nextHopRoutes[pkt->destination]],
                                pkt);
        }
    }
    else
    {
        cout << "Error, no interfaces exist" << endl;
    }
}

// Received count bytes from specified source
void Node::PacketArrival(Packet* pkt)
{
	//Decrement Time to live
    (pkt->timeToLive)--;
    if(pkt->timeToLive > 0) // Otherwise drop
    {
        // If the packet is destined for another node
        if(pkt->destination != address)
        {
            Send(pkt);  // Send the packet to another node
        }
        else
        {
            pktsReceived++;
            bytesReceived += pkt->count;
            // Pass the packet to all of the applications:
            for(unsigned int i = 0; i < applications.size(); ++i)
            {
                applications[i]->ReceivePacket(pkt);
            }
        }
    }
    else
    {
        cout << "TTL expired" << endl;
    }
}

// Schedule Application Starting
void Node::StartApplications()
{
    for(unsigned int i = 0; i < applications.size(); ++i)
    {
        // Start each application at a random time between 0 and 1 second
        Simulator::Schedule(drand48(), &Application::AppStart, this->applications[i]);
    }
}

// Return the # of drops at each interface
unsigned int Node::getDrops()
{
    unsigned int drops = 0;
    for(unsigned int i = 0; i < interfaces.size(); ++i)
    {
        drops += interfaces[i]->getDrops();
    }
    return drops;
}

// Print out application and interface statistics:
void Node::PrintStats()
{
    // Print Interface Stats:
    for(unsigned int i = 0; i < this->interfaces.size(); ++i)
    {
        interfaces[i]->PrintStats();
    }
    // Print Application Stats:
    for(unsigned int i = 0; i < this->applications.size(); ++i)
    {
        applications[i]->PrintStats();
    }
}





