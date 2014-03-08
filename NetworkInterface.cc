// Definition of NetworkInterface class
// ECE8893, Final Project, Fall 2012

/****** Description **************************************
 A NetworkInterface represents a single Point to Point network interface. It models a single NetworkLink object and a single Queue object to queue packets. It also maintains a busy ﬂag, indicating whether the interface is busy sending a packet or not. It must implement a Send and a Receive function to model sending and receiving packets. Finally it needs a pointer to the associated network node containing the interface.
 *********************************************************/

#include "NetworkInterface.h"
#include "DropTailQueue.h"
#include "NetworkLink.h"
#include "Simulator.h"
#include "Node.h"
#include <iostream>

using namespace std;


// Event1
template <typename T, typename OBJ, typename U1, typename T1>
void Event1<T, OBJ, U1, T1>::CallHandler()
{
    (obj->*handler)(t1);
}


// Constructors:
// Default Constructor
NetworkInterface::NetworkInterface()
: link(NULL), queue(NULL), node(NULL), busy(false), transmissionDelay(0)
{
  queue = new DropTailQueue(50);
}


// Member Functions
void NetworkInterface::AddP2PLink(NetworkLink* netLink)
{
  	link = netLink;
    link->thisInterface = this;
}

void NetworkInterface::Send(Packet* packet)
{
    // Add packet to Queue
    queue->Enque(packet);
    
    // If the queue isn't empty and the link isn't busy:
    if((queue->Empty() != true) && (busy == false))
    {
        Packet* pkt = queue->Deque();
        busy = true;
        Simulator::Schedule(transmissionDelay,
                            &NetworkLink::Send,
                            link, packet);
    }
}


// Receive Packet:
void NetworkInterface::PacketArrival(Packet* packet)
{
    // Let the node handle packet arrival:
    node->PacketArrival(packet);
}

//Transmission complete
void NetworkInterface::Tcomplete()
{
    // If the transmission is complete, try to send another packet
    if(queue->Empty() != true)
    {
        Packet* pkt = queue->Deque();
        busy = true;
        Simulator::Schedule(transmissionDelay,
                            &NetworkLink::Send,
                            link, pkt);
    }
    else
    {
        busy = false;
    }
}
// Print Interface Stats (# of dropped packets)
void NetworkInterface::PrintStats()
{
    cout << "Node[" << node->address << "] Packets Dropped at Interface: ";
    node->pktsDropped += queue->getDrops();
    queue->PrintStats();
    cout << endl;
}

unsigned int NetworkInterface::getDrops()
{
    return queue->getDrops();
}


