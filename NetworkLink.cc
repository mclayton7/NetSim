// Definition of NetworkLink class
// ECE8893, Final Project, Fall 2012
/****** Description **************************************
 A NetworkLink represents a single network “wire” connecting two network interfaces together. It must have two Node pointers representing the two ends of the point to point link, as well as a bandwidth (bits per second) and delay (seconds) to model the link’s characteristics.
 *********************************************************/
#include <iostream>
#include "Simulator.h"
#include "Node.h"
#include "NetworkLink.h"
#include "NetworkInterface.h"
#include "Packet.h"

using namespace std;


template <typename T, typename OBJ>
void Event0<T, OBJ>::CallHandler()
{
    (obj->*handler)();
}
template <typename T, typename OBJ, typename U1, typename T1>
void Event1<T, OBJ, U1, T1>::CallHandler()
{
    (obj->*handler)(t1);
} 

// Constructors:
// Default Constructor
NetworkLink::NetworkLink()
: peerNode(NULL), peerInterface(NULL), thisInterface(NULL), delay(1), dataRate(10000000)
{
    // Nothing Else to Do
    // Default delay of 1ms with a datarate of 10Mbit/s
}

NetworkLink::NetworkLink(double delay0, double dataRate0)
: peerNode(NULL), peerInterface(NULL), thisInterface(NULL), delay(delay0), dataRate(dataRate0)
{
	// Nothing Else to Do
}

// Member Functions
void NetworkLink::SetPeer(Node* node)
{
    peerNode = node;
}

// Send a Packet to a Peer
void NetworkLink::Send(Packet* packet)
{
	// Setup event in the future for peerNode's peerInterface to receive packet
    Time_t propDelay = ((packet->count * 8) / dataRate);
    Simulator::Schedule(propDelay + delay, &NetworkInterface::PacketArrival, peerInterface, packet);
    
    // Schedule Tcomplete when packet has been sent (and send other packets in queue)
    Simulator::Schedule(propDelay, &NetworkInterface::Tcomplete, thisInterface);
}
