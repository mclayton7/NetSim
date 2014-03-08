// Definition of NetworkInterface class
// ECE8893, Final Project, Fall 2012

#ifndef __NETWORK_LINK_H__
#define __NETWORK_LINK_H__

#include "Link.h"
class Node;
class Packet;
class NetworkInterface;


class NetworkLink : public Link
{
public:
    NetworkLink();                                  // Construtor
    NetworkLink(double delay0, double dataRate0);   // Construct with delay and data rate
    virtual void SetPeer(Node*);
    virtual void Send(Packet*);                     // Send a packet to peer
public:
    Node* peerNode;                     // The other node
    NetworkInterface* peerInterface;    // The other interface
    NetworkInterface* thisInterface;
    double delay;                       // Speed of light delay on this link (in milliseconds)
    double dataRate;                    // Bits per second on this link 10Mbit/s
};

#endif
