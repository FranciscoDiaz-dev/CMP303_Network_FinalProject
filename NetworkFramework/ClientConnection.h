#ifndef _CLIENT_CONNECTION_H
#define _CLIENT_CONNECTION_H
#pragma once

#include <vector>
#include "ConnectionBase.h"
#include "ServerInfo.h"
#include "../CMP303_Coursework_game/CMP303CourseworkGame/Tank.h"



class ClientConnection : public ConnectionBase
{
public:
	// constructor
	ClientConnection(Tank* player, int* gameId, GameState* gameState);
	// destructor
	~ClientConnection();

	// run the conexion to a server
	bool joinAGame(ServerInfo newServerInfo);

	bool exitAGame();

	// return the lastest players information saved/received on the server
	std::vector<TankInfo> getPlayersInfo(Tank* player, int* gameId, GameState* gameState);

private:
	ServerInfo serverInfo; // server information
	sf::TcpSocket tcpSocket; // client socket

	Tank* player;
	int* gameId;
	GameState* gameState;
};

#endif // _CLIENT_CONNECTION_H