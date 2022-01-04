#ifndef _CLIENT_CONNECTION_H
#define _CLIENT_CONNECTION_H
#pragma once

#include "ConnectionBase.h"
#include "ConnectionMessage.h"


class ClientConnection : public ConnectionBase
{
public:
	// constructor
	ClientConnection();
	// destructor
	~ClientConnection();

	// run the conexion to a server
	bool joinAGame(PlayerMessage* playerMsg, SockAddr toSockAddr);
};

#endif // _CLIENT_CONNECTION_H