// Definition of Application abstract base class
// ECE8893, Final Project, Fall 2012

/****** Description **************************************
 Application, OnOffApplication, and TrafficSyncApplication model network appliations that generate network trafﬁc and receive network trafﬁc. The abstract base class Application has Start and Stop pure virtual functions.
 *********************************************************/

#include "Application.h"
#include "Node.h"

Application::Application()
{
    // Nothing to construct (cause it's virtual!)
}


void Application::AttachToNode(Node* node)
{
    // Add this application to the node:
    node->AddApplication(this);
}

// Application Events:
void Application::AppStart()
{
    
}

void Application::AppStop()
{
    
}
