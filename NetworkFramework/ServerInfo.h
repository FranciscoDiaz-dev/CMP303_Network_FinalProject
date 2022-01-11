#ifndef _SERVER_INFO_H
#define _SERVER_INFO_H
#pragma once

// Server Info
// It contains all the information about a server
// It is used by Server List Manager mainly, gui and the client connection

#include <string>
#include <SFML\Network.hpp>
#include "SockAddr.h"

struct ServerInfo
{
	ServerInfo () : name(""), ipAddr("0.0.0.0"), udpPort(sf::Socket::AnyPort), tcpListenerPort(sf::Socket::AnyPort),
		sendUpdateRate(100.0f), fakeLatency(4.0f), maxNumPlayersPerGame(4), maxNumGames(2) {}

	// components
	std::string name;
	sf::IpAddress ipAddr;
	unsigned short udpPort; // udp port for updating players
	unsigned short tcpListenerPort; // port used by the tcp for determitant actions such as creating/deleting new games,players, etc it will use the same ip addr of the udp
	float sendUpdateRate; // milliseconds (ms)
	float fakeLatency; // milliseconds (ms)
	int maxNumPlayersPerGame; // maximum number of players per game can host at the same time
	int maxNumGames; // maximum number of games can host at the same time
};

#endif // _SERVER_INFO_H
