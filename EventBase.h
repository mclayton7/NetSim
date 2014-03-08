// Definition of Application abstract base class
// ECE8893, Final Project, Fall 2012

/****** Description **************************************
 Defines an abstract base class to handle events in typesafe event handling enviromnent 
 *********************************************************/

class EventBase
{
public:
    EventBase(Time_t t) : time(t) {}
public:
    Time_t time;                    // Timestamp for the vent
    virtual void CallHandler() = 0; // All subclasses must implement this
};


// Event Comparator Class for multiset
class event_less
{
public:
    event_less() { }
    inline bool operator()(EventBase* const & l, const EventBase* const & r) const {
        if(l->time < r->time) return true;
        return false;
    }
};
