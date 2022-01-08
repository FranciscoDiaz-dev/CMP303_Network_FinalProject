#ifndef _SERVER_INFO_H
#define _SERVER_INFO_H
#pragma once

#include <string>
#include <SFML\Network.hpp>
#include "SockAddr.h"

struct ServerInfo
{
	ServerInfo () : name(""), ipAddr("0.0.0.0"), udpPort(sf::Socket::AnyPort), tcpListenerPort(sf::Socket::AnyPort) {}

	// components
	std::string name;
	sf::IpAddress ipAddr;
	unsigned short udpPort;
	unsigned short tcpListenerPort; // port used by the tcp for creating deleting new games and players, it will the same ip addr of the udp
};

#endif // _SERVER_INFO_H
