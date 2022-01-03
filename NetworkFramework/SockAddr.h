#ifndef _SOCK_ADDR_H
#define _SOCK_ADDR_H
#pragma once

#include <SFML\Network.hpp>

struct SockAddr
{
	sf::IpAddress ipAddr;
	unsigned short port;
};

#endif // _SOCK_ADDR_H

