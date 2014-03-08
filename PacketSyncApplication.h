// Definition of PacketSyncApplication class
// ECE8893, Final Project, Fall 2012

#ifndef __PACKET_SYNC_APPLICATION_H__
#define __PACKET_SYNC_APPLICATION_H__

#include "Application.h"


class PacketSyncApplication  : public Application
{
public:
    PacketSyncApplication();    // Constructor
    virtual void AppStart();    // Start the application
    virtual void AppStop();     // Stop the application
    virtual void ReceivePacket(Packet* pkt);    // Receive a Packet
    virtual void PrintStats();                  // Print App Stats
private:
    int totalPacketsReceived;   // Total # of packets received by node
    int totalBytesReceived;     // Total # of bytes received by node
    bool state;                 // State of App (started or stopped)
};
#endif
