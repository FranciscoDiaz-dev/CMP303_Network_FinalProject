#ifndef _SERVER_BASE_H
#define _SERVER_BASE_H
#pragma once

#include "ConnectionMessage.h"

#include <winsock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

class ConnectionBase
{

public:
	// constructor
	ConnectionBase();
	// destructor
	~ConnectionBase();

	// Send a message to the server (or to anyone, in fact).
	bool sendMessage(TankMessage tank_msg, std::string to_ip, int to_port);
	// Read a response back from the server (or from anyone, in fact).
	TankMessage receiveMessage();

	// Print an error message and exit.
	void die(const char* message);

protected:
	SOCKET sock_;
};

#endif //SERVER_BASE_H
