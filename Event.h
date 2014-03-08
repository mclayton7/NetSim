// Definition of Event base class
// ECE8893, Final Project, Fall 2012

#ifndef __EVENT_H__
#define __EVENT_H__

typedef enum 
{
    NoEvent,
    // More event types here
    Arrival,
    Tcomplete,
    AppStart,
    AppStop
} Event_t;

class Event
{
public:
    Event() : ev(NoEvent) { }   // Default constructor
    Event(Event_t t) : ev(t) {} // Specific event constructor
    Event_t EventType();        // Return the event type
private:
    Event_t ev;
};
#endif


