#include "ConnectionBase.h"

ConnectionBase::ConnectionBase()
{
}

ConnectionBase::~ConnectionBase()
{
	printf("Quitting\n");
}

bool ConnectionBase::udpSendMessage(sf::Packet& packet, SockAddr& toSockAddr)
{
	printf("UDP Sending Message: ");

	sf::Socket::Status socketStatus = udpSocket.send(packet, toSockAddr.ipAddr, toSockAddr.port);

	// With UDP one dagram sent => one datagram received
	// so this while would not be used (only usseful for TCP)
	// however I have decided to use it just in case
	while (socketStatus == sf::Socket::Status::Partial)
	{
		socketStatus = udpSocket.send(packet, toSockAddr.ipAddr, toSockAddr.port);
		printf("Partial message sent.\n");
	}

	switch (socketStatus)
	{
	case sf::Socket::Status::Done:
		printf("Message sent to address:%s and port:%d.\n", toSockAddr.ipAddr.toString().c_str(), toSockAddr.port);
		return true;
		break;
	case sf::Socket::Status::Error:
		printf("Error sending message.\n");
		return false;
		break;
	case sf::Socket::Status::Disconnected:
		printf("Socket not available.\n");
		return false;
		break;
	case sf::Socket::Status::NotReady:
		printf("The socket is not ready to send data.\n");
		return false;
		break;
	}
}

bool ConnectionBase::udpReceiveMessage(sf::Packet* packet, SockAddr* fromSockAddr, bool alreadyWaited, sf::Time timeout)
{
	selector.add(udpSocket);

	if (alreadyWaited || selector.wait(timeout))
	{
		// Test if we have to read 
		if (!udpSocket.isBlocking() || selector.isReady(udpSocket))
		{
			printf("UDP Reading Message: ");

			sf::Socket::Status socketStatus = udpSocket.receive(*packet, fromSockAddr->ipAddr, fromSockAddr->port);

			// With UDP one dagram sent => one datagram received
			// so this while would not be used (only usseful for TCP)
			// however I have decided to use it just in case
			while (socketStatus == sf::Socket::Status::Partial)
			{
				socketStatus = udpSocket.receive(*packet, fromSockAddr->ipAddr, fromSockAddr->port);
				printf("Partial message received.\n");
			}

			switch (socketStatus)
			{
			case sf::Socket::Status::Done:
				printf("Message received from address:%s and port:%d.\n", fromSockAddr->ipAddr.toString().c_str(), fromSockAddr->port);
				return true;
				break;
			case sf::Socket::Status::Error:
				printf("Error receiving message.\n");
				return false;
				break;
			case sf::Socket::Status::Disconnected:
				printf("'From socket' not available.\n");
				return false;
				break;
			case sf::Socket::Status::NotReady:
				printf("Socket is not ready to receive data.\n");
				return false;
				break;
			}
		}
	}

	// timeout finished and none message was received
	return false;
}


bool ConnectionBase::tcpSendMessage(sf::Packet& packet, sf::TcpSocket& tcpSocket)
{
	printf("TCP Sending Message: ");

	sf::Socket::Status socketStatus = tcpSocket.send(packet);

	// make sure that all the data is sent (this is TCP)
	while (socketStatus == sf::Socket::Status::Partial)
	{
		socketStatus = tcpSocket.send(packet);
		printf("Partial message sent.\n");
	}

	switch (socketStatus)
	{
	case sf::Socket::Status::Done:
		printf("Message sent to address:%s and port:%d.\n", tcpSocket.getRemoteAddress().toString().c_str(), int(tcpSocket.getRemotePort()));
		return true;
		break;
	case sf::Socket::Status::Error:
		printf("Error sending message.\n");
		return false;
		break;
	case sf::Socket::Status::Disconnected:
		printf("Socket not available.\n");
		return false;
		break;
	case sf::Socket::Status::NotReady:
		printf("The socket is not ready to send data.\n");
		return false;
		break;
	}
}

bool ConnectionBase::tcpReceiveMessage(sf::Packet* packet, sf::TcpSocket& tcpSocket, bool alreadyWaited, sf::Time timeout)
{
	if (alreadyWaited || selector.wait(timeout))
	{
		// Test if we have to read 
		if (selector.isReady(tcpSocket))
		{
			printf("TCP Reading Message: ");

			sf::Socket::Status socketStatus = tcpSocket.receive(*packet);

			// make sure all the data is received (this is TCP)
			while (socketStatus == sf::Socket::Status::Partial)
			{
				socketStatus = tcpSocket.receive(*packet);
				printf("Partial message received.\n");
			}

			switch (socketStatus)
			{
			case sf::Socket::Status::Done:
				printf("Message received from address:%s and port:%d.\n", tcpSocket.getRemoteAddress().toString().c_str(), int(tcpSocket.getRemotePort()));
				return true;
				break;
			case sf::Socket::Status::Error:
				printf("Error receiving message.\n");
				return false;
				break;
			case sf::Socket::Status::Disconnected:
				printf("'From socket' not available.\n");
				return false;
				break;
			case sf::Socket::Status::NotReady:
				printf("Socket is not ready to receive data.\n");
				return false;
				break;
			}
		}
	}
	// timeout finished and none message was received
	return false;
}
