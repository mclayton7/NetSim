// Main program for NetSim
// ECE8893 Final Project, Fall 2012
//Group Members: Mac Clayton, Ifrah Saeed, and Amanda Cummings
#include <sys/time.h>
#include <stdlib.h>
#include <iostream>
#include "Application.h"
#include "CommonDefs.h"
#include "DropTailQueue.h"
#include "NetworkInterface.h"
#include "NetworkLink.h"
#include "Node.h"
#include "OnOffApplication.h"
#include "Packet.h"
#include "PacketSyncApplication.h"
#include "Queue.h"
#include "Simulator.h"


// Global variables:
double RHO = 1.0;               // Ranges from 0-1, 0.5 default
double RATE = RHO * 10000000.0; // 10Mbps
double MEANOFF = 0.5;           // Range from 0-1
double MEANON  = 0.5;           // Range from 0-1


using namespace std;
// Simulator static objects
Simulator*  Simulator::instance = 0;
EventSet_t Simulator::events;
NodeList_t  Simulator::nodes;
bool        Simulator::stopped = false;
Time_t      Simulator::now = 0;


void CreateNetwork()
{
    //
    // This could probably be refactored into a couple of arrays...
    //

    //Create all of the leaf nodes
    Node* H00 = new Node();
    Node* H01 = new Node();
    Node* H02 = new Node();
    Node* H03 = new Node();
    
    Node* H10 = new Node();
    Node* H11 = new Node();
    Node* H12 = new Node();
    Node* H13 = new Node();
    
    Node* H20 = new Node();
    Node* H21 = new Node();
    Node* H22 = new Node();
    Node* H23 = new Node();
    
    Node* H30 = new Node();
    Node* H31 = new Node();
    Node* H32 = new Node();
    Node* H33 = new Node();
    
    //Create all of the applications for the leaves and add them to the leaves
    PacketSyncApplication* a = new PacketSyncApplication();
    OnOffApplication* b = new OnOffApplication(RATE, MEANOFF, MEANON);
    H00->AddApplication(a);
    H00->AddApplication(b);
    PacketSyncApplication* c = new PacketSyncApplication();
    OnOffApplication* d = new OnOffApplication(RATE, MEANOFF, MEANON);
    H01->AddApplication(c);
    H01->AddApplication(d);
    PacketSyncApplication* e = new PacketSyncApplication();
    OnOffApplication* f = new OnOffApplication(RATE, MEANOFF, MEANON);
    H02->AddApplication(e);
    H02->AddApplication(f);
    PacketSyncApplication* h = new PacketSyncApplication();
    OnOffApplication* i = new OnOffApplication(RATE, MEANOFF, MEANON);
    H03->AddApplication(h);
    H03->AddApplication(i);
    
    PacketSyncApplication* j = new PacketSyncApplication();
    OnOffApplication* k = new OnOffApplication(RATE, MEANOFF, MEANON);
    H10->AddApplication(j);
    H10->AddApplication(k);
    PacketSyncApplication* l = new PacketSyncApplication();
    OnOffApplication* m = new OnOffApplication(RATE, MEANOFF, MEANON);
    H11->AddApplication(l);
    H11->AddApplication(m);
    PacketSyncApplication* n = new PacketSyncApplication();
    OnOffApplication* o = new OnOffApplication(RATE, MEANOFF, MEANON);
    H12->AddApplication(n);
    H12->AddApplication(o);
    PacketSyncApplication* p = new PacketSyncApplication();
    OnOffApplication* q = new OnOffApplication(RATE, MEANOFF, MEANON);
    H13->AddApplication(p);
    H13->AddApplication(q);
    
    PacketSyncApplication* r = new PacketSyncApplication();
    OnOffApplication* s = new OnOffApplication(RATE, MEANOFF, MEANON);
    H20->AddApplication(r);
    H20->AddApplication(s);
    PacketSyncApplication* t = new PacketSyncApplication();
    OnOffApplication* u = new OnOffApplication(RATE, MEANOFF, MEANON);
    H21->AddApplication(t);
    H21->AddApplication(u);
    PacketSyncApplication* v = new PacketSyncApplication();
    OnOffApplication* w = new OnOffApplication(RATE, MEANOFF, MEANON);
    H22->AddApplication(v);
    H22->AddApplication(w);
    PacketSyncApplication* a1 = new PacketSyncApplication();
    OnOffApplication* b1 = new OnOffApplication(RATE, MEANOFF, MEANON);
    H23->AddApplication(a1);
    H23->AddApplication(b1);
    
    PacketSyncApplication* c1 = new PacketSyncApplication();
    OnOffApplication* d1 = new OnOffApplication(RATE, MEANOFF, MEANON);
    H30->AddApplication(c1);
    H30->AddApplication(d1);
    PacketSyncApplication* e1 = new PacketSyncApplication();
    OnOffApplication* f1 = new OnOffApplication(RATE, MEANOFF, MEANON);
    H31->AddApplication(e1);
    H31->AddApplication(f1);
    PacketSyncApplication* g1 = new PacketSyncApplication();
    OnOffApplication* h1 = new OnOffApplication(RATE, MEANOFF, MEANON);
    H32->AddApplication(g1);
    H32->AddApplication(h1);
    PacketSyncApplication* i1 = new PacketSyncApplication();
    OnOffApplication* j1 = new OnOffApplication(RATE, MEANOFF, MEANON);
    H33->AddApplication(i1);
    H33->AddApplication(j1);
    
    //Create all of the r nodes
    Node* R00 = new Node();
    Node* R01 = new Node();
    
    Node* R10 = new Node();
    Node* R11 = new Node();
    
    Node* R20 = new Node();
    Node* R21= new Node();
    
    Node* R30 = new Node();
    Node* R31 = new Node();

    
    //Create all of the links between the r nodes and h nodes
    R00->AddNeighbor(H00);
    R00->AddNeighbor(H01);
    R01->AddNeighbor(H02);
    R01->AddNeighbor(H03);
    
    R10->AddNeighbor(H10);
    R10->AddNeighbor(H11);
    R11->AddNeighbor(H12);
    R11->AddNeighbor(H13);
    
    R20->AddNeighbor(H20);
    R20->AddNeighbor(H21);
    R21->AddNeighbor(H22);
    R21->AddNeighbor(H23);
    
    R30->AddNeighbor(H30);
    R30->AddNeighbor(H31);
    R31->AddNeighbor(H32);
    R31->AddNeighbor(H33);
    
    //Create all of the g nodes
    Node* G0 = new Node();
    Node* G1 = new Node();
    Node* G2 = new Node();
    Node* G3 = new Node();
    
    //Create all of the links between r and g nodes
    G0->AddNeighbor(R00);
    G0->AddNeighbor(R01);
    G1->AddNeighbor(R10);
    G1->AddNeighbor(R11);
    G2->AddNeighbor(R20);
    G2->AddNeighbor(R21);
    G3->AddNeighbor(R30);
    G3->AddNeighbor(R31);
    
    G0->AddNeighbor(G1, true);
    G0->AddNeighbor(G2, true);
    G0->AddNeighbor(G3, true);
    G1->AddNeighbor(G2, true);
    G1->AddNeighbor(G3, true);
    G2->AddNeighbor(G3, true);
    
    //Add all nodes to simulation
    Simulator::nodes.push_back(H00);
    Simulator::nodes.push_back(H01);
    Simulator::nodes.push_back(H02);
    Simulator::nodes.push_back(H03);
    Simulator::nodes.push_back(H10);
    Simulator::nodes.push_back(H11);
    Simulator::nodes.push_back(H12);
    Simulator::nodes.push_back(H13);
    Simulator::nodes.push_back(H20);
    Simulator::nodes.push_back(H21);
    Simulator::nodes.push_back(H22);
    Simulator::nodes.push_back(H23);
    Simulator::nodes.push_back(H30);
    Simulator::nodes.push_back(H31);
    Simulator::nodes.push_back(H32);
    Simulator::nodes.push_back(H33);
    Simulator::nodes.push_back(R00);
    Simulator::nodes.push_back(R01);
    Simulator::nodes.push_back(R10);
    Simulator::nodes.push_back(R11);
    Simulator::nodes.push_back(R20);
    Simulator::nodes.push_back(R21);
    Simulator::nodes.push_back(R30);
    Simulator::nodes.push_back(R31);
    Simulator::nodes.push_back(G0);
    Simulator::nodes.push_back(G1);
    Simulator::nodes.push_back(G2);
    Simulator::nodes.push_back(G3);
}

int main()
{
    //seeding random numner generator
    struct timeval tv;
    gettimeofday(&tv,0);
    srand48(tv.tv_usec);        
    for(int i = 1; i < 11; i++)
    {
      RHO = (double)i/10.0;                    // Increment from 0.1 - 1.0 by 0.1
        RATE = RHO * 10000000.0; // 10Mbps
        MEANOFF = 0.5;           // Range from 0-1
        MEANON  = 0.5;           // Range from 0-1
        Simulator::instance = 0;    // Set Simulator instance
        Simulator::events.clear();  // Clear events
        Simulator::nodes.clear();   // Clear nodes
        Simulator::stopped = false; // Reset Stop flag
        Simulator::now = 0;         // Reset Start time
        Node::count = 0;            // Reset Node addressing
        CreateNetwork();            // Generate Network
        Simulator::ComputeRoutes(); // Compute Routing Tables

        //Start all applications:
        for(unsigned int i = 0; i < Simulator::nodes.size(); ++i)
        {
            Simulator::nodes[i]->StartApplications();
        }
        Simulator::StopAt(100); // Run for 100 Seconds
        cout << "Running Simulation..." << endl;
        Simulator::Run();
        cout << "Simulation Complete" << endl;
        cout << "Printing Statistics: RHO = " << RHO << endl;
        Simulator::PrintStats();
    }
}
