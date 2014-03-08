# Makefile for NetSim
# ECE8893 Final Project, Fall 2012

OBJECTS = NetSim.o Application.o OnOffApplication.o PacketSyncApplication.o DropTailQueue.o Packet.o NetworkLink.o NetworkInterface.o Node.o Simulator.o myBFS.o


NetSim:	$(OBJECTS)
	g++ -o NetSim $(OBJECTS)

compile:
	g++ -c  Packet.cc
	g++ -c  Application.cc
	g++ -c  OnOffApplication.cc
	g++ -c  PacketSyncApplication.cc
	g++ -c  DropTailQueue.cc
	g++ -c  NetworkLink.cc
	g++ -c  NetworkInterface.cc
	g++ -c  Node.cc
	g++ -c  Simulator.cc
	g++ -c  myBFS.cc

clean:
	rm -f $(OBJECTS)


