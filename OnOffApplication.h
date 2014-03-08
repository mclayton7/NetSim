// Definition of OnOffApplication class
// ECE8893, Final Project, Fall 2012

#ifndef __ON_OFF_APPLICATION_H__
#define __ON_OFF_APPLICATION_H__

#include "Application.h"

class OnOffApplication  : public Application
{
public:
    OnOffApplication(double rate0, double meanOffTime0, double meanOnTime0);
            void SetPeerAddress(int peerAddr);
    virtual void AppStart();                    // Start the application
    virtual void AppStop();                     // Stop the application
    virtual void ReceivePacket(Packet* pkt);    // Receive packet
    virtual void PrintStats();                  // Print App statistics
private:
    double          rateWhenOn;     // bits per second
    double          packetSize;     // Size of packets to generate
    double          meanOffTime;    // Avg time in off state
    double          meanOnTime;     // Avg time in on state
    unsigned int    peerAddress;    // Address of node to send packets
    unsigned int    nStates;        // # of state changes
    
};

#endif
