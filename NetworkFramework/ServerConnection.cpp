#include "ServerConnection.h"



ServerConnection::ServerConnection(string serverIdentifier, ServerInfo& serverInfo)
	: serverId(serverIdentifier), maxNumPlayersPerGame(4), maxNumGames(2), ConnectionBase()
{
	// Bind the UDP socket to the ip iddress and the udp port
	if (udpSocket.bind(serverInfo.udpPort, serverInfo.ipAddr) != sf::Socket::Done)
	{
		printf("Server UDP socket bound failed to address:%s, port:%d\n", serverInfo.ipAddr.toString().c_str(), serverInfo.udpPort);
	}
	else
	{
		printf("Server UDP socket bound to address:%s, port:%d\n", serverInfo.ipAddr.toString().c_str(), serverInfo.udpPort);
	}

	// Set TCP listener listen to the ip iddress and the tcp listener port
	if (tcpListener.listen(serverInfo.tcpListenerPort, serverInfo.ipAddr) != sf::Socket::Done)
	{
		printf("Server TCP listener failed on listening to address: %s, port:%d\n", serverInfo.ipAddr.toString().c_str(), serverInfo.tcpListenerPort);
	}
	else
	{
		printf("Server TCP Listener is listening to address:%s, port:%d\n", serverInfo.ipAddr.toString().c_str(), serverInfo.tcpListenerPort);
		// Add the listener to the selector
		selector.add(tcpListener);
	}

	// add the tcp listenrr and udp sockets to the selector
	selector.add(tcpListener);
	selector.add(udpSocket);
}

ServerConnection::~ServerConnection()
{
	for (GameInfo* gameInfo : activeGames)
	{
		// delete all the player Data
		for (std::pair<SockAddr, TankInfo>* playerData : gameInfo->playersData)
		{
			delete playerData;
			playerData = nullptr;
		}
		// delete the game
		delete gameInfo;
		gameInfo = nullptr;
	}
}


void ServerConnection::run(sf::Time timeout)
{
	// Make the selector wait for data on any socket
	if (selector.wait(timeout))
	{
		// Check if there are any important request from the player such as joining a game, leaving a game or wining
		if(!checkTcpNewConnection())
			// Process TCP request if they are available
			processTcpRequests();



		processUdpRequests();
		
	}
}


string ServerConnection::getActiveGamesInfo()
{
	string activeGamesInfo;

	activeGamesInfo += "Active Games: " + std::to_string(activeGames.size()) + "\n";

	if (!activeGames.empty())
	{
		for (GameInfo* gameInfo : activeGames)
		{
			activeGamesInfo += "Game ID: " + std::to_string(gameInfo->id) + "\n";

			for (std::pair<SockAddr, TankInfo>* playerData : gameInfo->playersData)
			{
				activeGamesInfo += " - Player ID: " + std::to_string(playerData->second.id) + "\n";
			}
		}
	}

	return activeGamesInfo;
}


PlayerData* ServerConnection::createPlayerData(GameInfo* hostGame, TankInfo& newTankInfo)
{
	// Step 1:
	// Create Player Id
	// The current number of players will be the player id
	// for example: if there are not player (numPlayers == 0)
	// then the first player id of this game will be 0
	newTankInfo.id = int(hostGame->playersData.size());

	// Step 2:
	// Set initial player posity by its id
	switch (newTankInfo.id)
	{
	case 0:
		newTankInfo.x = 40.0f;
		newTankInfo.y = 40.0f;
		break;
	case 1:
		newTankInfo.x = 40.0f;
		newTankInfo.y = 70.0f;
		break;
	case 3:
		newTankInfo.x = 40.0f;
		newTankInfo.y = 100.0f;
		break;
	case 4:
		newTankInfo.x = 40.0f;
		newTankInfo.y = 140.0f;
		break;
	}
	// Step 2:
	// Add player info to the collection of that game and their socket address
	//hostGame->playersData.push_back();

	// Step 4:
	// Add the player to the game counter
	//hostGame->numPlayers++;

	// return the last player added
	return new PlayerData(SockAddr(), newTankInfo);
}

GameInfo* ServerConnection::createNewGame()
{
	// creata a new game info object
	GameInfo* gameInfo = new GameInfo(int(activeGames.size()));
	return gameInfo;
}


GameInfo* ServerConnection::findGameInfoById(int id)
{
	// find the game where the player who sent the message is playing
	for (GameInfo* gameInfo : activeGames)
	{
		if (gameInfo->id == id)
		{
			return gameInfo;
		}
	}

	return nullptr;
}

PlayerData* ServerConnection::findPlayerDataById(GameInfo* gameInfo, int playerId)
{
	if (gameInfo == nullptr)
		return nullptr;

	// find the game where the player who sent the message is playing
	for (PlayerData* playerData : gameInfo->playersData)
	{
		if (playerData->second.id == playerId)
		{
			return playerData;
		}
	}

	return nullptr;
}

int ServerConnection::getAGameIdCanHost()
{
	for (int i = 0; i < int(activeGames.size()); i++)
	{
		// check if that game can host a new player
		if (activeGames.at(i)->numPlayers < maxNumPlayersPerGame)
			return i;
	}

	// there are not games which can host a new player
	return -1;
}


void ServerConnection::processUdpRequests()
{
	// create a socket address where we will save the data of the socket we receive the message
	// as we want to send a message back to them
	SockAddr fromSockAddr;
	PlayerMessage receivedPlayerMsg;

	// Listening the player Message
	sf::Packet packetReceived;
	bool msgReceived = udpReceiveMessage(&packetReceived, &fromSockAddr, true); // don't wait again, just check if this socket is ready
	packetReceived >> receivedPlayerMsg;

	// UPDATE Request //
	if (msgReceived && receivedPlayerMsg.requestType == int(RequestType::UPDATE))
	{
		// Get the game info where the player is
		GameInfo* gameInfo = findGameInfoById(receivedPlayerMsg.gameId);
		PlayerData* playerData = findPlayerDataById(gameInfo, receivedPlayerMsg.gameId);

		// If the player and game have been found:
		if (gameInfo != nullptr && playerData != nullptr)
		{
			// update the player info in the servers if the time in which this information
			// was sent is later than the one we currently have
			//if (gameInfo->playersInfo.at(receivedPlayerMsg.tankInfo.id).time < receivedPlayerMsg.tankInfo.time)
			//{
				// update player information on the server
			playerData->second = receivedPlayerMsg.tankInfo;
			playerData->first = fromSockAddr;

			// Send the most updated version of all the players to every player 
			for (PlayerData* toPlayerData : gameInfo->playersData)
			{
				sf::Packet packetToPlayer;

				// Convert all the data to sf::Packet
				for (PlayerData* playerData : gameInfo->playersData)
				{
					packetToPlayer << playerData->second;
				}

				// send message
				udpSendMessage(packetToPlayer, toPlayerData->first);
			}
		}
	}
}


bool ServerConnection::checkTcpNewConnection()
{
	// Test the listener if it is ready to accept a new connection
	if (selector.isReady(tcpListener))
	{
		// The listener is ready: there is a client which wants to connect
		sf::TcpSocket* client = new sf::TcpSocket;
		if (tcpListener.accept(*client) == sf::Socket::Done)
		{
			// Add the new client to the clients list
			pendingTcpRequests.push_back(client);
			// Add the new client to the selector so that we will
			// be notified when he sends something
			selector.add(*client);

			printf("TCP Client accepted with address:%s and port:%d.\n", client->getRemoteAddress().toString().c_str(), int(client->getRemotePort()));
			return true;
		}
		else
		{
			// Error, we won't get a new connection, delete the socket
			delete client;
			return false;
		}
	}
}

void ServerConnection::processTcpRequests()
{
	// Check client by client socket if it is ready to be ready from them
	for (std::list<sf::TcpSocket*>::iterator it = pendingTcpRequests.begin(); it != pendingTcpRequests.end(); ++it)
	{
		sf::TcpSocket& client = **it;

		// The client has sent some data, we can receive it
		sf::Packet receivedPacket;
		if (tcpReceiveMessage(&receivedPacket, client))
		{
			PlayerMessage receivedPlayerMessage;
			// transform the packet received to player message structure
			receivedPacket >> receivedPlayerMessage;

			/* Detect what the player wants */
			if (receivedPlayerMessage.requestType == int(RequestType::JOIN))
			{
				processTcpJoinAGameRequest(receivedPlayerMessage, client);
			}
			else if (receivedPlayerMessage.requestType == int(RequestType::EXIST))
			{
				processTcpExitAGameRequest(receivedPlayerMessage, client);
			}
		}		
	}

	// remove any processed tcp request
	removeProcessedTCPRequests();
}

void ServerConnection::processTcpJoinAGameRequest(PlayerMessage& receivedPlayerMessage, sf::TcpSocket& client)
{
	printf("\tProcessing request: Join a new game.\n");

	// create objects where the information related with this player will be saved
	PlayerData* newPlayerData = nullptr;
	GameInfo* hostGame = nullptr;

	// Find/create a game which can host
	// There are different results/option for this request:
	// 
	// OPTION 1.1: There are active games which can host a new player
	if (int(activeGames.size()) > 0 && getAGameIdCanHost() != -1)
	{
		printf("\t\tOption 1: There are a active game can host.\n");

		// Add this new player to a game which is waiting for players
		// get the game is waiting
		hostGame = activeGames.at(getAGameIdCanHost()); // get the game which can host
	}
	// OPTION 1.2: There are not active games which can host a new player
	// however the server CAN host a new game
	else if (int(activeGames.size()) < maxNumGames)
	{
		printf("\t\tOption 2: There aren't any active game can host, however the server can create a new game.\n");

		// Add this player to a new game
		// create the new game.
		// the id of the game will be the index position of the vector container
		hostGame = createNewGame();
		activeGames.push_back(hostGame);
	}

	// If a game which can host a new player has been found then create the player
	// and send to them their initial info (game id, player id, player pos, etc
	if (hostGame != nullptr)
	{
		// create a new player info
		newPlayerData = createPlayerData(hostGame, receivedPlayerMessage.tankInfo);

		// update the received message player with the game id assigned and their player id
		PlayerMessage toPlayerMessage;
		toPlayerMessage.gameId = hostGame->id;
		toPlayerMessage.gState = int(GState::WAITING_ROOM);
		toPlayerMessage.tankInfo = newPlayerData->second;

		sf::Packet sentPacket;
		sentPacket << toPlayerMessage;

		if (tcpSendMessage(sentPacket, client))
		{
			// save the player data
			printf("The player did receive the message.\n");
			hostGame->playersData.push_back(newPlayerData);
			hostGame->numPlayers += 1;

			// set this client request as done (ready to be removed)
			tcpRequestsToRemove.push_back(&client);
		}
		else
		{
			printf("The player did not receive the message aparently, so delet it.\n");
			delete newPlayerData;
			newPlayerData = nullptr;
		}
	}
	// If there are not active games which can host a new player and
	// the server CANNOT host a new game
	else
	{
		printf("This server cannot host any new players.");
	}
}

void ServerConnection::processTcpExitAGameRequest(PlayerMessage& receivedPlayerMessage, sf::TcpSocket& client)
{
	printf("Processing request: Exist the game.\n");

	// create objects where the information related with this player will be saved
	GameInfo* gameInfo = findGameInfoById(receivedPlayerMessage.gameId);
	PlayerData* playerData = findPlayerDataById(gameInfo, receivedPlayerMessage.tankInfo.id);

	auto removeIt = std::find(gameInfo->playersData.begin(), gameInfo->playersData.end(), playerData);
	if (removeIt != gameInfo->playersData.end())
	{
		gameInfo->playersData.erase(removeIt);
		gameInfo->numPlayers--;

		// set this client request as done (ready to be removed)
		tcpRequestsToRemove.push_back(&client);
	}
}


void ServerConnection::removeProcessedTCPRequests()
{
	while (tcpRequestsToRemove.begin() != tcpRequestsToRemove.end()) // while it exits states to remove
	{
		removeTCPRequest(*tcpRequestsToRemove.begin()); // delete the client
		tcpRequestsToRemove.erase(tcpRequestsToRemove.begin()); // and erase from the container of tcp request to remove as it has been already removed
	}
}

void ServerConnection::removeTCPRequest(sf::TcpSocket* client)
{
	auto removeIt = std::find(pendingTcpRequests.begin(), pendingTcpRequests.end(), client);
	if (removeIt != pendingTcpRequests.end())
	{
		// remove it from the selector
		selector.remove(*client);
		// remove it from the collection
		pendingTcpRequests.erase(removeIt);
	}
}