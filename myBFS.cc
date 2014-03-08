// Definition of BFS Library for computing Routes
// ECE8893, Final Project, Fall 2012

/****** Description **************************************
 The BFS Library contains two functions that are used to generate routing tables in the Network Simulation. 
 myBFS computes the routes using a Breadth-First-Search algorithm. makingTable uses the results of myBFS 
 to generate a routing table in nextHopRoutes. This is a vector in each node where the index corresponds 
 to the destination node, and the integer inside is the interface on the current node that should be used to send the packet
 *********************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include "CommonDefs.h"
#include "Node.h"
#include "NetworkInterface.h"
#include "Simulator.h"
#include "NetworkLink.h"

using namespace std;


typedef enum
{
  WHITE,
  GRAY,
  BLACK
}colors_t;


// Global Variables
vector<int> colors; //0 (WHITE) if node not visited, 1 (GRAY) if node is being processed, 2 (BLACK) if node is done
vector<int> distances;
vector<Node*> parents;    
queue<Node*> myQueue;


////BFS
void myBFS(Node* node)
{
    //reset vectors for each node
    colors.clear();
    distances.clear();
    parents.clear();
    for(unsigned int i = 0; i < Simulator::nodes.size(); i++)
    {
        colors.push_back(WHITE);
        distances.push_back(-1);
        parents.push_back(NULL);
        node->nextHopRoutes.push_back(-1);
    }
    colors[node->address] = GRAY;
    distances[node->address] = 0;
    parents[node->address] = NULL;
    myQueue.push(node);
    while(!myQueue.empty())
    {
        Node* u = myQueue.front();
        myQueue.pop();
        //check its neighbors in for loop
        for(unsigned int i = 0; i < u->interfaces.size(); i++)
        {
            Node* v = u->interfaces[i]->link->peerNode; //neighbor
            if(colors[v->address] == WHITE)
            {
                colors[v->address] = GRAY;
                distances[v->address] = distances[u->address] + 1;
                parents[v->address] = u;
                myQueue.push(v);
            }
        }
        colors[u->address] = BLACK;
    }
}

//making routing table
void makingTable(Node* node)
{
    for(unsigned int i = 0; i < Simulator::nodes.size(); i++)
    {
        Node* temp;
        if(i != node->address)
        {
            temp = Simulator::nodes[i];
            //back trace the parents pointers until the original node is found. the peer node of original node is next hop node
            while(parents[temp->address]->address != node->address)
            {
                temp = parents[temp->address];
            }
            int index = 0;
            for(unsigned int j = 0; j<node->interfaces.size(); j++)
            {
                if(node->interfaces[j]->link->peerNode->address == temp->address)
                {
                    index = j;
                    break;
                }
            }
            node->nextHopRoutes[i] = index;
        }
    }
}


