#ifndef _SERVER_CONNECTION_H
#define _SERVER_CONNECTION_H
#pragma once

#include "ConnectionBase.h"

class ServerConnection : public ConnectionBase
{

public:
	// constructor
	ServerConnection(std::string server_ip, int server_port);
	// destructor
	~ServerConnection();

	// run the conexion to a client
	void run(std::string to_ip, int to_port);
};

#endif // _SERVER_CONNECTION_H

