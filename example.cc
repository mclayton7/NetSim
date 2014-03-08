// A simple trivial Discrete Event Simulator to illustrate DES concepts
// This one is slightly less trivial than des-simple1.cc

// George F. Riley, Georgia Tech, Fall 2011 ECE8893

#include <math.h> // For random numbers
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h> //for srand

// Start by defining an abstract base class called "Handler" that all
// event handlers will derive from.  A pointer to a Nandler is stored
// in the sorted (by timestamp) event list. The timestamp is the "key"
// and the pointer to the Handler is the "value".

using namespace std;

// Keep trace of time with a double-precision float
typedef double Time_t;

// create enumerations for the known event types
typedef enum 
  {
    ARRIVAL,
    DEPARTURE,
    CRASHED
  } AircraftEvents_t;

// Create an "Event" class that describes the actual event type.
// This might be subclassed  if the various event types need additional
// data
class Event 
{
public:
  Event(int et0) : eventType(et0) {}
public:
  int eventType;
};

  
class Handler 
{
public:
  Handler() { }      // Nothing needed for constructor
  virtual ~Handler() {}; // Virtual destructor
  virtual void Handle(Time_t t, Event*) = 0;  // Handle an event at time "t"
};

// Define a class modeling an  "Airport" that 
// is an event handler.  In this simple example, the "event" is
// an airplane arrival.  The handler for the event simply schedules
// a airplane arrival for one of it's neighbors at a random future
// time

class Airport : public Handler 
{
public:
  Airport(int id0) : id(id0), totalArrivals(0), totalOnGround(0) {};
  virtual void Handle(Time_t t, Event*);  // Define the event handler
  void SetPeer(Airport* n);  // Give the node a pointer to its peer
public:
  int   id;
  int   totalArrivals;
  int   totalOnGround;
  vector<Airport*> peers;
};

// Define the STL Map container that maintains the sorted event
// list.
typedef pair<Handler*, Event*> HandlerPair_t;
typedef multimap<Time_t, HandlerPair_t> EventList_t;
typedef EventList_t::value_type EventPair_t;

// Define the Simulator class that maintains the event list
// and runs the simulation.  Note the simulator object is also
// a handler, as it needs to process the "Stop" event.
class Simulator : Handler
{
public:
  Simulator();
  void Handle(Time_t t, Event*);
   // Schedule a new event "t" hours in the future.  Handler is "h"
  static void Schedule(Time_t t, Handler* h, Event* ev);
  static void Run(); // Run the simulation until the stop time is reached
  static void StopAt(Time_t t);     // Stop the simulation at time "t"
  static Time_t Now();              // Return current simulation tiome
  static Simulator* instance;       // Points to singleton simulator object
private:
  static EventList_t events;
  static bool        stopped;
  static Time_t      now;
  };

// Implementations for Simulator object

Simulator::Simulator()
{
  instance = this;
}

void Simulator::Handle(Time_t t, Event*)
{ // Since "Stop" is only event (for now) we don't need the event
  cout << "Simulator handing stop event at time " << t << endl;
  stopped = true;
}

void Simulator::Schedule(Time_t t, Handler* h, Event* ev)
{ // Insert new event in the sorted event queue
  // Note that time "t" is time in the future
  events.insert(EventPair_t(Now () + t, HandlerPair_t(h, ev)));
}

void Simulator::Run()
{
  while (!stopped && !events.empty())
    {
      // Get the next event
      EventPair_t currentEvent = *events.begin();
      // Remove drom que
      events.erase(events.begin());
      // Advance Simulation Time
      now = currentEvent.first;  // Time of event
      HandlerPair_t hp = currentEvent.second;
      Handler* h = hp.first;     // Pointer to event handler
      Event*   ev = hp.second;   // Pointer to the event
      h->Handle(now, ev);        // Call the handler
    }
}

void Simulator::StopAt(Time_t t)
{
  Simulator::Schedule(t - Simulator::Now(), Simulator::instance, 0);
}

Time_t Simulator::Now()
{
  return now;
}

// Simulator static objects
EventList_t Simulator::events;
bool        Simulator::stopped = false;
Time_t      Simulator::now = 0;
Simulator*  Simulator::instance = 0;

// Implementations for the Airport object
// First the handler
void Airport::Handle(Time_t t, Event* ev)
{ // Here the event is either an arrival or departure
  if (ev->eventType == ARRIVAL)
    {
      cout << "Airport " << id << " got arrival event at time " << t << endl;
      totalArrivals++;
      totalOnGround++;
      // Choose a random time for "at gate" 0 to 2 hour
      double atGate = drand48() * 2.0;
      Event* dpEvent = new Event(DEPARTURE);
      Simulator::Schedule(atGate, this, dpEvent);
    }
  else if (ev->eventType == DEPARTURE)
    {
      cout << "Airport " << id << " got departure event at time " << t << endl;
      // Schedule arrival at another airport
      Time_t flightTime = drand48() * 10;
      int    peer = drand48() * peers.size();
      Event* arEvent = new Event(ARRIVAL);
      // The event will be handled "flightTime" in the future by the
      // randomly selected peer.
      Simulator::Schedule(flightTime, peers[peer], arEvent);
      // And decrement "on ground" count
      totalOnGround--;
    }
  else
    {
      cout << "Oops, unknown event type in ariport handler" << endl;
    }
}

void Airport::SetPeer(Airport* p)
{
  peers.push_back(p);
}

int main()
{
  // We need an object of class Simulator to handle simulator events
  Simulator simulator;
  // Seed the random number generator to get different random values
  // on each run
  struct timeval tv;
  gettimeofday(&tv, 0);
  srand48(tv.tv_usec);
  
  // First create the airports
  vector<Airport*> airports;
  for (int i = 0; i < 10; ++i)
    {
      Airport* ap = new Airport(i);
      airports.push_back(ap);
    }
  // Now set connecting airports (randomly)
  for (unsigned i = 0; i < airports.size(); ++i)
    {
      for (unsigned j = 0; j < airports.size(); ++j)
        {
          double rand = drand48();
          if (rand < 0.5)
            { // set peer with 50% probability
              airports[i]->SetPeer(airports[j]);
            }
        }
    }
  // now schedule some  arrivals at each airport 
  for (unsigned i = 0; i < airports.size(); ++i)
    {
      for (unsigned j = 0; j  < 15; ++j)
        {
          double rand = drand48();
          if (rand < 0.3)
            { // Schedule an arrival with 30% probability
              Event* arEvent = new Event(ARRIVAL);
              Simulator::Schedule(drand48() * 8, airports[i], arEvent);
            }
        }
    }
  // Set the stop time
  Simulator::StopAt(500.0); // Model 500 hours of activity
  Simulator::Run();         // Run the simulation
  cout << "Simulation Complete" << endl;
  // Print some arrival statistics for each airport
  for (unsigned i = 0; i < airports.size(); ++i)
    {
      cout << "Airport " << i 
           << " totalArrivals " << airports[i]->totalArrivals
           << " total on ground " << airports[i]->totalOnGround
           << endl;
    }
}
