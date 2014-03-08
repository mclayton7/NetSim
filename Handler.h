// Definition of Handler abstract base class
// ECE8893, Final Project, Fall 2012

#ifndef __HANDLER_H__
#define __HANDLER_H__

#include "CommonDefs.h"

class Event;

class Handler
{
public:
    virtual void Handle(Event*, Time_t) = 0;
};

#endif