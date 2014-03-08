// Definition of NetworkInterface class
// ECE8893, Final Project, Fall 2012

#ifndef __NETWORK_INTERFACE_H__
#define __NETWORK_INTERFACE_H__

#include "CommonDefs.h"
#include "DropTailQueue.h"

class NetworkLink;
class Packet;
//class DropTailQueue;

class NetworkInterface
{
public:
    NetworkInterface();             // Constructor
    void AddP2PLink(NetworkLink*);  // Add link to another node
    void Send(Packet*);             // Send specified packet to p2p peer
    void PacketArrival(Packet*);    // Receive Packet
    void Tcomplete();               // Done sending a packet
    void PrintStats();              // Print interface stats
    unsigned int getDrops();
public:
    NetworkLink*    link;   // Link that connects interface
    DropTailQueue*  queue;  // Queue that holds packets
    Node*           node;   // The node this interface attaches to
    bool            busy;   // true if busy sending a packet
    Time_t          transmissionDelay;
};

#endif



