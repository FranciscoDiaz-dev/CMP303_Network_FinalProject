#ifndef _CLIENT_CONNECTION_H
#define _CLIENT_CONNECTION_H
#pragma once

#include "../../NetworkFramework/ConnectionBase.h"
#include "../../NetworkFramework/ConnectionMessage.h"

class ClientConnection : public ConnectionBase
{
public:
	// constructor
	ClientConnection();
	// destructor
	~ClientConnection();

	// run the conexion to a server
	void run(PlayerMessage tank_msg);
};

#endif // _CLIENT_CONNECTION_H