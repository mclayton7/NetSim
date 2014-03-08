// Definition of Link abstract base class
// ECE8893, Final Project, Fall 2012

#ifndef ___Link_H__
#define ___Link_H__

class Node;
class Packet;

class Link
{
public:
  Link(){};
    virtual void SetPeer(Node*) = 0;
    virtual void Send(Packet*) = 0;
};

#endif
