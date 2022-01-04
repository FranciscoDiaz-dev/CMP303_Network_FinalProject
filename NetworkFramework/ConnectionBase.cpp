#include "ConnectionBase.h"

ConnectionBase::ConnectionBase()
{
}

ConnectionBase::~ConnectionBase()
{
	// We won't actually get here, but if we did then we'd want to clean up...
	printf("Quitting\n");
}

bool ConnectionBase::udpSendMessage(sf::Packet packet, SockAddr toSockAddr, sf::Time timeout)
{
	printf("Sending Message:\n");

	if (udpSocket.send(packet, toSockAddr.ipAddr, toSockAddr.port) != sf::Socket::Done)
	{
		printf("Error sending message.\n");
		return false;
	}
	else
	{
		printf("Message sent to ip:%s and port:%d.\n", toSockAddr.ipAddr.toString().c_str(), toSockAddr.port);
		return true;
	}
}

bool ConnectionBase::udpReceiveMessage(sf::Packet* packet, SockAddr* fromSockAddr, sf::Time timeout)
{
	// add the socket to the selector
	selector.add(udpSocket);

	if (selector.wait(timeout))
	{
		// Test if we have to read 
		if (selector.isReady(udpSocket))
		{
			printf("Reading Message:\n");

			if (udpSocket.receive(*packet, fromSockAddr->ipAddr, fromSockAddr->port) != sf::Socket::Done)
			{
				printf("Error receiving message.\n");
				return false;
			}
			else
			{
				printf("Message received from ip:%s and port:%d.\n", fromSockAddr->ipAddr.toString().c_str(), fromSockAddr->port);
				return true;
			}
		}
	}

	// timeout finished and none message was received
	return false;
}