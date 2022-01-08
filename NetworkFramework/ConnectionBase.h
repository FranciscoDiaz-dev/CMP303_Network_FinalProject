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
	bool udpSendMessage(sf::Packet packet, SockAddr toSockAddr);

	// Read a response back from the server (or from anyone, in fact).
	bool udpReceiveMessage(sf::Packet* packet, SockAddr* fromSockAddr, sf::Time timeout = sf::microseconds(1.0f));

	// Send a message to the server (or to anyone, in fact).
	bool tcpSendMessage(sf::Packet packet, sf::TcpSocket* tcpSocket);

	// Read a response back from the server (or from anyone, in fact).
	bool tcpReceiveMessage(sf::Packet* packet, sf::TcpSocket& tcpSocket, sf::Time timeout = sf::microseconds(1.0f));

protected:
	sf::UdpSocket udpSocket;
	sf::SocketSelector selector;
};

#endif //CONNECTION_BASE_H