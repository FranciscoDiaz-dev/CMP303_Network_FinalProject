#ifndef _SERVER_CONNECTION_H
#define _SERVER_CONNECTION_H
#pragma once

#include <vector>
#include <string>
#include "ConnectionBase.h"
#include "GameInfo.h"
#include "ServerInfo.h"

using std::string;

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

private:
	string serverId;
	bool isRunning;

	std::vector<GameInfo*> activeGames;
	int maxNumPlayersPerGame;
	int maxNumGames;

	void addNewPlayer(GameInfo* gameInfo, SockAddr playerSockAddr, PlayerInfo newPlayerInfo);

	// return the game id which can host a new player
	// if there are not games which can host a new player it will return -1
	int getAGameIdCanHost();

	// Return a game info pointer which has that id
	GameInfo* getGameInfoById(int id);
};

#endif // _SERVER_CONNECTION_H

