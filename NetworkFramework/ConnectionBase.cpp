#include "ConnectionBase.h"

ConnectionBase::ConnectionBase()
{
}

ConnectionBase::~ConnectionBase()
{
	// We won't actually get here, but if we did then we'd want to clean up...
	printf("Quitting\n");
}

bool ConnectionBase::sendMessage(sf::Packet packet, SockAddr toSockAddr, sf::Time timeout)
{
	printf("\nSending Message:\n");

	if (socket.send(packet, toSockAddr.ipAddr, toSockAddr.port) != sf::Socket::Done)
	{
		printf("Error sending message.");
		return false;
	}
	else
	{
		printf("Message sent to ip:%s and port:%d", toSockAddr.ipAddr.toString(), toSockAddr.port);
		return true;
	}
}

sf::Packet ConnectionBase::receiveMessage(SockAddr* fromSockAddr, sf::Time timeout)
{
	sf::Packet packet; // variable where the message will be saved, if it fails, it will return a message with id == -1

	if (fromSockAddr != nullptr && selector.wait(timeout))
	{
		// Test if we have to read 
		if (selector.isReady(socket))
		{
			printf("\nReading Message:\n");

			if (socket.receive(packet, fromSockAddr->ipAddr, fromSockAddr->port) != sf::Socket::Done)
			{
				printf("Error receiving message.");
			}
			else
			{
				printf("Message received from ip:%s and port:%d", fromSockAddr->ipAddr.toString(), fromSockAddr->port);
			}
		}
	}

	return packet;
}