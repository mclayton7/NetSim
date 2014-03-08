// Definition of Simulator class
// ECE8893, Final Project, Fall 2012
/****** Description **************************************
 The Simulator object maintains the sorted pending event 
 list and a list of all Node objects in the simulation. 
 Further, the Simulator needs to add Stop, Run, StopAt, 
 Schedule and ComputeRoutes functions. There is a single 
 instance of the Simulator object in every simulation.
 *********************************************************/
#include <iostream>
#include <vector>
#include "Simulator.h"
#include "Node.h"
#include "Application.h"

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
Simulator::Simulator()
{
    instance = this;
}

// Member Functions
void Simulator::Stop()
{
	// Clear list of events which will stop simulation
    stopped = true;
}

void Simulator::Run()
{
  while (!stopped && !events.empty())
    {
        // Get the next event
        EventBase* currentEvent = *events.begin();
        events.erase(events.begin());   // Remove from queue
        now = currentEvent->time;       // Advance Simulation Time
        currentEvent->CallHandler();    // call the event
    }

}

// Set time to end simulation:
void Simulator::StopAt(Time_t t)
{
  Simulator::Schedule(t - Simulator::Now(),
                        &Simulator::Stop,
                        Simulator::instance);
}

// Return time Now
Time_t Simulator::Now()
{
    return now;
}

// Compute routing tables at every node
void Simulator::ComputeRoutes()
{
	for(unsigned int i = 0; i < nodes.size(); ++i)
    {
        nodes[i]->ComputeRoutes();
    }
}

// Print out Simulation statistics:
void Simulator::PrintStats()
{
    unsigned int totalPktsSent = 0;
    unsigned int totalPktsReceived = 0;
    unsigned int totalBytesSent = 0;
    unsigned int totalBytesReceived = 0;
    unsigned int packetsDropped = 0;
    for(unsigned int i = 0; i < nodes.size(); ++i)
    {
        
        packetsDropped += nodes[i]->getDrops();
        totalPktsSent += nodes[i]->pktsSent;
        totalBytesSent += nodes[i]->bytesSent;
        totalPktsReceived += nodes[i]->pktsReceived;
        totalBytesReceived += nodes[i]->bytesReceived;
    }
    cout << " *******  Simulation Statistics:  *******  " << endl;
    cout << "                      Total Packets Sent:   " << totalPktsSent << endl;
    cout << "                        Total Bytes Sent:   " << totalBytesSent << endl;
    cout << "                  Total Packets Received:   " << totalPktsReceived << endl;
    cout << "                    Total Bytes Received:   " << totalBytesReceived << endl;
    cout << "                   Total Packets Dropped:   " << packetsDropped << endl;
    cout << "     Network Efficiency (1 - drops/sent):   " << (double)(totalPktsSent - packetsDropped)/totalPktsSent << endl;
    cout << "    Network Efficiency (received / sent):   " << (double)totalPktsReceived/totalPktsSent << endl;
}
