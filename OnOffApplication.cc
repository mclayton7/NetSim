// Definition of OnOffApplication class
// ECE8893, Final Project, Fall 2012
/****** Description **************************************
 Application, OnOffApplication, and TrafficSyncApplication model network appliations that generate network trafﬁc and receive network trafﬁc. The abstract base class Application has Start and Stop pure virtual functions.

 The OnOffApplication creates and sends packets addressed to a speciﬁed peer node at a constant rate when in the “on” state.
 *********************************************************/

// If rho is 0.9, we generate data for 2*rho or 1.8ms

#include <cstdlib>
#include <iostream>
#include "Packet.h"
#include "Simulator.h"
#include "OnOffApplication.h"

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


// Constructors:
// Default Constructor
OnOffApplication::OnOffApplication(double rate0, double meanOffTime0, double meanOnTime0)
: rateWhenOn(rate0), packetSize(1492), meanOffTime(meanOffTime0), meanOnTime(meanOnTime0),
  peerAddress(0), nStates(0)
{
    // Nothing Else to Do
}

// Member Functions:
void OnOffApplication::SetPeerAddress(int peerAddr)
{
	peerAddress = peerAddr;
}

// Start the Application
void OnOffApplication::AppStart()
{
    nStates++;  // Count the # of times the app switches from on to off
	// Send a burst of packets for a random amount of time, and then stop
    // Assume packet size = MTU = 1492 bytes = 11936 bits
    Time_t onTime = drand48() * (2 * meanOnTime);   // Length of time to be on
    Time_t Xmit = onTime * rateWhenOn;              // Amount of data can be transmitted (bits)
    int nPackets = Xmit / (packetSize * 8);
    Time_t dt = onTime / nPackets;
    // Choose random address to send (nodes 0 - 15 are leaf nodes, so use % (n + 1)):
    int randAddress = rand() % 16;
    while(randAddress == node->address)             // Make sure we don't send to ourself
    {
        randAddress = rand() % 16;  
    }
    for(double i = 0; i < (onTime-dt); i += dt)
    {
        // Create Packet:
        Packet* pkt = new Packet(node->address, randAddress, packetSize);
        // Increment counters in node:
        node->pktsSent++;
        node->bytesSent += pkt->count;
        // Schedule Packet to be sent:
        Simulator::Schedule(i, &Node::Send, node, pkt);
    }
    // Schedue Off App:
    Simulator::Schedule(onTime, &OnOffApplication::AppStop, this);
}

// Stop the Application
void OnOffApplication::AppStop()
{
    nStates++;  // Increment states
    Time_t time = drand48() * (2 * meanOffTime);    // Compute time be off
    Simulator::Schedule(time, &OnOffApplication::AppStart, this);
}

void OnOffApplication::ReceivePacket(Packet* pkt)
{
	//Do nothing
}

// Print out the number of times the Application has turned on and off
void OnOffApplication::PrintStats()
{
    cout << "Node[" << node->address << "] On/Off App switched states: " << nStates << endl;
}
