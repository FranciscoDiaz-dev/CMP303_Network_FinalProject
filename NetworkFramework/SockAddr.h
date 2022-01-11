#ifndef _SOCK_ADDR_H
#define _SOCK_ADDR_H
#pragma once

// Socket Address
// It contains the ip and port for a sfml socket
// Useful for containing the data organised

#include <SFML\Network.hpp>

struct SockAddr
{
	// constructors
	SockAddr() : ipAddr("0.0.0.0"), port(sf::Socket::AnyPort) {} // Any ip address and any port
	SockAddr(sf::IpAddress ip, unsigned short sockectPort) : ipAddr(ip), port(sockectPort) {}

	// components
	sf::IpAddress ipAddr;
	unsigned short port;
};

#endif // _SOCK_ADDR_H

