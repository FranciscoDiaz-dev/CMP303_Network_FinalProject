#ifndef _SERVER_CONNECTION_H
#define _SERVER_CONNECTION_H
#pragma once

#include <vector>
#include <list>
#include <string>
#include "ConnectionBase.h"
#include "GameInfo.h"
#include "ServerInfo.h"
#include "ConnectionMessage.h"

using std::string;

class ServerConnection : public ConnectionBase
{

public:
	// constructor
	ServerConnection(string serverIdentifier, ServerInfo& serverInfo);
	// destructor
	~ServerConnection();

	// run the conexion to a client
	void run(sf::Time timeout = sf::microseconds(1.0f));

	// return the info of the server
	string getActiveGamesInfo();

private:
	/* Server Characterics */
	string serverId;
	int maxNumPlayersPerGame;
	int maxNumGames;


	/* Server Data */
	std::vector<GameInfo*> activeGames;

	// Functions to create data on this serve data //

	// create the player data into the host game and return a pointer to that player data created
	PlayerData* createPlayerData(GameInfo* gameInfo, TankInfo& newTankInfo);

	// create a new game
	GameInfo* createNewGame();

	// Functions to find information on the database of this server //

	// Return a game info pointer which has that id,
	// if it doesn't find it then it returns nullptr
	GameInfo* findGameInfoById(int id);

	// return the player information
	PlayerData* findPlayerDataById(GameInfo* gameInfo, int playerId);

	// Return the game id which can host a new player
	// if there are not games which can host a new player it will return -1
	int getAGameIdCanHost();


	/* UDP */

	// Process Update a Game (UP request)
	void processUdpRequests();


	/* TCP */

	// TCP Listener 
	sf::TcpListener tcpListener;
	// A list to store the future clients tcp requests
	std::list<sf::TcpSocket*> pendingTcpRequests;
	// A list to store the clients tcp request which has been processed
	std::list<sf::TcpSocket*> tcpRequestsToRemove;

	// Accept new tcp connections if there are any available
	bool checkTcpNewConnection();
	// Process the pending tcp requests if any of the tcp socket is ready to receive data (reading from them)
	void processTcpRequests();
	// Process Join a Game (TCP request)
	void processTcpJoinAGameRequest(PlayerMessage& receivedPlayerMessage, sf::TcpSocket& client);
	// Process Leave a Game (TCP request)
	void processTcpExitAGameRequest(PlayerMessage& receivedPlayerMessage, sf::TcpSocket& client);
	// Process to remove all the request which has been set to be removed because they have been already processed
	void removeProcessedTCPRequests();
	// Remove from the pending tcp requests list, and selector, all TCP client sockets
	// which they requests have been already solved
	void removeTCPRequest(sf::TcpSocket* client);
};

#endif // _SERVER_CONNECTION_H

