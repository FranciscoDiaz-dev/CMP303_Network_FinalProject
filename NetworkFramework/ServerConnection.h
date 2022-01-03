#ifndef _SERVER_CONNECTION_H
#define _SERVER_CONNECTION_H
#pragma once

#include <map>
#include "ConnectionBase.h"
#include "GameInfo.h"
#include "ServerInfo.h"

class ServerConnection : public ConnectionBase
{

public:
	// constructor
	ServerConnection(string serverIdentifier, ServerInfo& serverInfo);
	// destructor
	~ServerConnection();

	// run the conexion to a client
	void run();

	// return the info of the server
	bool getIsRunning() const { return isRunning; };
	string getServerId() const { return serverId; };

	void addNewPlayer(GameInfo* gameInfo, SockAddr playerSockAddr);

	// return the game id which can host a new player
	// if there are not games which can host a new player then return -1
	int gameIDCanHost();

	// return a game which is not full of players
	GameInfo getAvailableGame();

private:
	string serverId;
	bool isRunning;

	std::map<int, GameInfo> activeGames;
	int maxNumPlayersPerGame;
	int maxNumGames;
};

#endif // _SERVER_CONNECTION_H

