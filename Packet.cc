// Definition of Packet class
// ECE8893, Final Project, Fall 2012

/****** Description **************************************
 A Packet represents bytes being transmitted on the network. Your Packet model needs a size (length in bytes) a source identiﬁer (indicating the packet’s origin node address, and a destination indicating the ultimate destination address of the packet.
 *********************************************************/

#include "Packet.h"

// Constructors:

// Default Constructor
Packet::Packet()
: source(0), destination(0), count(0), timeToLive(64), seq(0)
{
	// Set TTL to default of 64
}

// Alternate Constructor
Packet::Packet(int source0, int destination0, int count0)
: source(source0), destination(destination0), count(count0), timeToLive(64), seq(0)
{
	// Nothing To Do Here
}
