// Definition of Node class
// ECE8893, Final Project, Fall 2012

#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include "Packet.h"

class NetworkInterface;
class Application;

class Node 
{
public:
    Node();                     // Constructor
    void ComputeRoutes();       // Populate the routing table
    void AddNeighbor(Node*, bool highspeed = false);    // Connect this node to that
    void AddApplication(Application*);                  // Add App to node
    void Send(Packet*);             // Send a Packet
    void PacketArrival(Packet*);    // Packet Arrival
    void StartApplications();       // Start all associated Apps
    unsigned int getDrops();        // Get # of packets dropped on interfaces
    void PrintStats();              // Print node statistics
public:
    unsigned int                    address;        // This node's address
    unsigned int                    pktsSent;       // # of packets sent
    unsigned int                    pktsReceived;   // # of packets received
    unsigned int                    bytesSent;      // # of bytes sent
    unsigned int                    bytesReceived;  // # of bytes received
    unsigned int                    pktsDropped;    // # of packets dropped by interface
    static int                      count;          // Static addressing variable
    std::vector<NetworkInterface*>  interfaces;     // All associated interfaces
    std::vector<Application*>       applications;   // All assicated apps
    std::vector<int>                nextHopRoutes;  // Routing table
};
  
#endif
