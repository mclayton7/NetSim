// Definition of Simulator class
// ECE8893, Final Project, Fall 2012

#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include <map>
#include <vector>
#include "CommonDefs.h"
#include "EventBase.h"

class Node;


//////////////// Event Class //////////////////////////////
template<typename T, typename OBJ>
class Event0 : public EventBase
{ // Event class with no arguments
  // Type T is the object type for the event handler object
  // Type OBJ is the actual event handler object
public:
    Event0(double t, void (T::*f)(void), OBJ* obj0)
    : EventBase(t), handler(f), obj(obj0){}
    void (T::*handler)(void);
    OBJ*      obj;
public:
    void CallHandler();
};

template<typename T, typename OBJ, typename U1, typename T1>
class Event1 : public EventBase
{
public:
    Event1(double t, void (T::*f)(U1), OBJ* obj0, T1 t1_0)
    : EventBase(t), handler(f), obj(obj0), t1(t1_0){}
    void (T::*handler)(U1);
    OBJ*      obj;
    T1        t1;
public:
    void CallHandler();
};


/////////////// Simulator Class ////////////////////////////
class Simulator
{
public:
    Simulator();
    void        Stop();             // Stop time has been reached
    static void Run();              // Run the simulation until the stop time is reached
    static void StopAt(Time_t t);   // Stop the simulation at time "t"
    static      Time_t Now();       // Return current simulation tiome
    static void ComputeRoutes();    // Compute routing tables at every node
    static void PrintStats();
    
    
    // Define the templated schedule functions
    // This one has zero arguments on the handler callback
    template <typename T, typename OBJ>
    static void Schedule(double t, void(T::*handler)(void), OBJ* obj)
    {
        EventBase* ev = new Event0<T, OBJ>(t + Simulator::Now(), handler, obj);
        events.insert(ev);
    }
    
    template <typename T, typename OBJ,
    typename U1, typename T1>
    static void Schedule(double t, void(T::*handler)(U1), OBJ* obj, T1 t1)
    {
        EventBase* ev = new Event1<T, OBJ, U1, T1>(t + Simulator::Now(), handler, obj, t1);
        events.insert(ev);
    }
    
public:
    // Member Variables
	static Simulator*   instance;   // Simulator Instance
    static NodeList_t   nodes;      // Vector of all nodes in simulation
	static bool         stopped;    // true if simulation stopped
	static Time_t       now;        // "current" time
    static EventSet_t  events;      // multiset of events
};



#endif
