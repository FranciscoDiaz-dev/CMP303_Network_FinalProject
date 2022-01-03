#ifndef _CONNECTION_BASE_H
#define _CONNECTION_BASE_H
#pragma once


#include "SockAddr.h"
#include <SFML\Network.hpp> // SFML Lib can't be static if we use sfml objt in this project classes

class ConnectionBase
{

public:
	// constructor
	ConnectionBase();
	// destructor
	~ConnectionBase();

	// Send a message to the server (or to anyone, in fact).
	bool sendMessage(sf::Packet packet, SockAddr toSockAddr, sf::Time timeout = sf::seconds(1.f));

	// Read a response back from the server (or from anyone, in fact).
	sf::Packet receiveMessage(SockAddr* fromSockAddr = nullptr, sf::Time timeout = sf::seconds(1.f));

protected:
	sf::UdpSocket socket; 
	sf::SocketSelector selector;
};

#endif //CONNECTION_BASE_H
