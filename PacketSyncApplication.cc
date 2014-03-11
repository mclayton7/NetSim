// Definition of PacketSyncApplication class
// ECE8893, Final Project, Fall 2012

/****** Description **************************************
 The packet sync applications simply count the number of recieved packets.
 *********************************************************/
#include <iostream>
#include "PacketSyncApplication.h"

using namespace std;

// Constructor:
// Default Constructor
PacketSyncApplication::PacketSyncApplication()
: totalPacketsReceived(0), totalBytesReceived(0), state(false)
{
	// Nothing Else to Do
}

// Member Functions:
// Start the application
void PacketSyncApplication::AppStart()
{
	state = true;
}
// Stop the application
void PacketSyncApplication::AppStop()
{
	state = false;
}

void PacketSyncApplication::ReceivePacket(Packet* pkt)
{
    if(state)
    {
        totalPacketsReceived++;             // Increment packets received
        totalBytesReceived += pkt->count;   // Add packet bytes to total
    }
    delete pkt;
}

// Print out Application Statistics
void PacketSyncApplication::PrintStats()
{
    cout << "Node[" << node->address << "] packets received: "
         << totalPacketsReceived << ", bytes received: "
         << totalBytesReceived << endl;
}