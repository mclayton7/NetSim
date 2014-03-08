// Common definitions for NetSim
// ECE8893 Final project, Fall 2012

#ifndef __COMMON_DEFS_H__
#define __COMMON_DEFS_H__

#include <set>
#include <vector>

class Node;
class EventBase;
class event_less;

// Type of simulation time variable, units of seconds.
typedef double Time_t;
// Set of sorted Events: 
typedef std::multiset<EventBase*, event_less> EventSet_t;
// List of Nodes:
typedef std::vector<Node*>  NodeList_t;

#endif
