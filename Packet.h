// Definition of Packet class
// ECE8893, Final Project, Fall 2012

#ifndef __PACKET_H__
#define __PACKET_H__

class Packet 
{
public:
    Packet(); // Default constructor
    Packet(int source0, int destination0, int count0);
public:
    int source;         // Source Node address
    int destination;    //Destination Node Address
    int count;          // Number of bytes
    int timeToLive;     // Time to Live (start at 64 as a guess)
    int seq;            // Sequence number (not used)
};

#endif
