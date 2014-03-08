// Definition of DropTail Queue class
// ECE8893, Final Project, Fall 2012

#ifndef __DROP_TAIL_QUEUE_H__
#define __DROP_TAIL_QUEUE_H__

#include <deque>
#include "Queue.h"

class Packet;


class DropTailQueue : public Queue
{
public:
    DropTailQueue(int maxLth);      // Create with specified maximum length (packets)
    virtual bool Enque(Packet*);    // Add a packet to the queue, true if successful
    virtual Packet* Deque();        // Remove a packet from the queue
    virtual bool Empty();           // Returns true if empty
    virtual void PrintStats();      // Prints Queue stats (# of drops)
    unsigned int getDrops();
private:
    std::deque<Packet*> packetQue;  // Container for packets
    int max;                        // Maximum length of queue
    unsigned int dropCount;         // Number of dropped Packets
};

#endif
