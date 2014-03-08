// Definition of Application abstract base class
// ECE8893, Final Project, Fall 2012

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "CommonDefs.h"
#include "Packet.h"
#include "Node.h"

class Application
{
public:
    Application();                      // Default constructor
    virtual void AttachToNode(Node*);   // Attach this application to a node
    virtual void AppStart() = 0;        // Start the application
    virtual void AppStop()  = 0;        // Stop the application
    virtual void ReceivePacket(Packet* pkt) = 0;    // Recieve a Packet
    virtual void PrintStats() = 0;                  // Print App stats
public:
    Node* node;     // Associated node
};


#endif
