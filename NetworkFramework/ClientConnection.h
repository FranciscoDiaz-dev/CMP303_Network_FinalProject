#ifndef _CLIENT_CONNECTION_H
#define _CLIENT_CONNECTION_H
#pragma once

#include <vector>
#include "ConnectionBase.h"
#include "ServerInfo.h"
#include "TankInfo.h"
#include "RequestType.h"

class Tank;
class EnemiesManager;
class GameState;

class ClientConnection : public ConnectionBase
{
public:
	// constructor
	ClientConnection(Tank* tank, EnemiesManager* enemiesManager, int* currentGameId, GameState* currentGameState);
	// destructor
	~ClientConnection();

	// ask the server to join a game, return true if it has joined
	bool joinAGame(ServerInfo newServerInfo);

	// inform the server this player wants to exit the game
	bool exitTheGame();

	// return the lastest players information saved/received on the server
	bool sendThisPlayerInfoToServer();

	std::vector<TankInfo> getEnemiesInfos();

private:
	ServerInfo serverInfo; // server information
	sf::TcpSocket tcpSocket; // client socket

	Tank* player;
	EnemiesManager* enemiesMgr;
	int* gameId;
	GameState* gameState;
};

#endif // _CLIENT_CONNECTION_H