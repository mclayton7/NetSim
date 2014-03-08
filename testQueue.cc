//
//  testQueue.cc
//  
//
//  Created by Mac Clayton on 11/21/12.
//
//
#include <iostream>
#include "DropTailQueue.h"
#include "Packet.h"

using namespace std;
int main()
{
    DropTailQueue* q = new DropTailQueue(10);
    int packetNumber = 0;
    while(true)
    {
        packetNumber++;
        Packet* p = new Packet(packetNumber,
                               packetNumber + 1,
                               packetNumber * 100);
        if(!q->Enque(p)) break;
    }
    cout << "Packet Number is: " << packetNumber << endl;
    while(true)
    {
        Packet* p = q->Deque();
        if(!p) break;
        cout << "packet size is: " << p->count << " src: " << p->source
        << " dst: " << p->destination << endl;
    }
}
