#ifndef _CLIENT_CONNECTION_H
#define _CLIENT_CONNECTION_H
#pragma once

#include "ConnectionBase.h"

class ClientConnection : public ConnectionBase
{

public:
	// constructor
	ClientConnection();
	// destructor
	~ClientConnection();

	// run the conexion to a server
	void run(TankMessage tank_msg, std::string to_ip, int to_port);
};

#endif // _CLIENT_CONNECTION_H