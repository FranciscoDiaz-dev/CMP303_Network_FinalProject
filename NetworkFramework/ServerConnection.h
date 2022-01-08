#ifndef _SERVER_CONNECTION_H
#define _SERVER_CONNECTION_H
#pragma once

#include <vector>
#include <list>
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

	string getActiveGamesInfo();

private:
	string serverId;
	bool isRunning;


	std::vector<GameInfo*> activeGames;
	int maxNumPlayersPerGame;
	int maxNumGames;

	// create the player data into the host game and return a pointer to that player data created
	PlayerData* createPlayerData(GameInfo* gameInfo, TankInfo& newTankInfo);

	// return the game id which can host a new player
	// if there are not games which can host a new player it will return -1
	int getAGameIdCanHost();

	// Return a game info pointer which has that id,
	// if it doesn't find it then it returns nullptr
	GameInfo* findGameInfoById(int id);

	// return the player information
	PlayerData* findPlayerDataById(GameInfo* gameInfo, int playerId);

	GameInfo* createNewGame();

	// TCP Listener 
	sf::TcpListener tcpListener;
	// Create a list to store the future clients
	std::list<sf::TcpSocket*> clients;

	void acceptNewConnection(sf::Time timeout = sf::Time::Zero);
};

#endif // _SERVER_CONNECTION_H

