NetSim
======
For more information:
[http://macclayton.com/projects/network-simulator/](http://macclayton.com/projects/network-simulator/)

A Discrete event simulation for a network

## To Build:
Just run `make` to build the application

## To Run:
To execute the application, type `./NetSim` to execute.

# Intro
A [Discrete event simulator](http://en.wikipedia.org/wiki/Discrete_event_simulation) is a type of simulator that revolves around a <em>state</em> that only changes when triggered by an <em>Event Queue</em>. It keeps track of time, and that time is only incremented by popping events off the Event Queue. Below is an overview of the Simulator's components, and a highlighting of some member variables.

1. `Node` - The node object represents a single network node, either a router or endpoint (computer, printer iPhone, etc.). A Node model contains:
    * `address`: The address of the node (For simulation purposes, this is an integer starting at zero).
    * `pktsSent`: The number of packets sent.
    * `pktsReceived`: The number of packets received.  
2. `NetworkInterface` - A Network Interface represents a single network connection.
    * `link`: A pointer to the link that connects the interface to a `NetworkLink`.
    * `queue`: A pointer to a Queue that holds the packets to be sent. There are many different types of Queues, but for this simulation, we will use a [Drop Tail Queue](http://en.wikipedia.org/wiki/Tail_drop).
3. `NetworkLink` - A Network Link mimics half of a "wire" that connects two Network Interfaces. The model contains:
    * `Node`: A pointer that represent the ends of the link. I
    * `bandwidth` (bits per second): The speed of the interface.
    * `delay` (milliseconds):Speed of light delay on the link, which models the wire's real world characteristics.
    * `dataRate` (bits-per-second): The [data rate](http://en.wikipedia.org/wiki/Data_rate_units) of the link.
4. `Packet` - A Packet represents bytes being transmitted across the network. The Packet model has:
    * `size` (length in bytes): Simulate the data being carried by the Packet.
    * `source`: The identity of the packet's origin.
    * `destination`: The intended recipient of the data.
    * `timeToLive`: The [TTL](http://en.wikipedia.org/wiki/Time_to_live) of a packet.
5. `Queue` - Queue is actually an abstract base class that `DropTailQueue` extends.
6. `Application` - The Application Models allow us to not only simulate programs running on a `Node`, but also capture statistical data.
7. `Simulator` - The simulator object manages the sorted pending event list (sorted by time) and a list of all of the Node objects in the simulation. It has Start, Stop, Run, Schedule, and ComputeRoutes function. There is only one instance of a Simulator object in the simulation.

## Memory Management
For the sake of this application, memory management will be ignored for brevity. 

# Rho (ρ)
To simulate real world usage, every host node has an `OnOffApplication` that sends data to a random address at a random interval between 0 and 1 second. Then it turns off for another random interval. This cycling simulates data being sent across a network. Rho (ρ) is a value between 0 and 1 that sets the amount of data sent during an Applications "on" state. The higher the Rho, the larger the amount of data being sent across the networks.

# Running the Simulation and Collecting Statistics
To setup the simulation, a network must first be constructed. Lines 43 - 218 show the creation of the nodes and the initialization of the various applications. Because each host node has a `PacketSyncApplication` that collects packet statistics, we can measure the following:
1. Total Packets Sent
2. Total Bytes sent
3. Total Packets Recieved
4. Total Bytes Recieved
5. Total Packets Dropped
6. Network Efficiency