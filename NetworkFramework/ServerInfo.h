#ifndef _SERVER_INFO_H
#define _SERVER_INFO_H
#pragma once

#include <string>
#include <SFML\Network.hpp>
#include "SockAddr.h"

struct ServerInfo
{
	ServerInfo () : name("") {}
	// components
	std::string name;
	SockAddr sockAddr;
};

#endif // _SERVER_INFO_H
