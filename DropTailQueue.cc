// Definition of DropTail Queue class
// ECE8893, Final Project, Fall 2012

/*********************************************************
 Queue and DropTailQueue model basic network queuing methods. Createn abstract base class Queue with pure functions Enqueue and Dequeue. Enque returns a boolean indicating the packet was successfully enqueued, and Dequeue returns a packet pointer of the packet being dequeued. The queue class also needs MaxSize and CurrentSize member functions indicating the maximum queue length and current queue length respectively. The DropTailQueue is a simple ﬁrst-in ﬁrst-out queue with a hard limit that drops packets if the queue is full (ie. the size has reached the maximum size).
 *********************************************************/
#include <iostream>
#include "DropTailQueue.h"

using namespace std;

// Constructor:
DropTailQueue::DropTailQueue(int maxLth)
    : max(maxLth)
{
    // Nothing Else to Do
    dropCount = 0;
}


// Member Functions:
// Add Packet to Que
bool DropTailQueue::Enque(Packet* packet)
{
	if(packetQue.size() < max)
	{
		packetQue.push_back(packet);
		return true;    // return true if < max
	}
	else
	{
        ++dropCount;    // Increment for dropped packet
		return false;   // Return false if full
	}
}

// Return and Remove First Packet from Que
Packet* DropTailQueue::Deque()
{
	if(packetQue.size() != 0)
    {
		Packet* tempPkt = packetQue.front();
		packetQue.pop_front();
		return tempPkt;
	}
	else
	{
		return NULL;
	}
}

// Returns true if queue empty
bool DropTailQueue::Empty()
{
    return packetQue.empty();
}

void DropTailQueue::PrintStats()
{
    cout << dropCount;
}

// Return the number of drops from the queue
unsigned int DropTailQueue::getDrops()
{
    return dropCount;
}
