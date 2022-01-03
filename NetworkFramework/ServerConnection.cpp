#include "ServerConnection.h"
#include "ConnectionMessage.h"
#include "CustomizedPacketOperators.h"


ServerConnection::ServerConnection(string serverIdentifier, ServerInfo& serverInfo)
	: serverId(serverIdentifier), maxNumPlayersPerGame(2), maxNumGames(2), ConnectionBase()
{
	// bind the socket to the ip iddress and the port
	if (socket.bind(serverInfo.sockAddr.port, serverInfo.sockAddr.ipAddr) != sf::Socket::Done)
	{
		printf("Server socket bound failed to address %s, port %d\n", serverInfo.sockAddr.ipAddr.toString().c_str(), serverInfo.sockAddr.port);
		isRunning = false;
	}
	else
	{
		// ntohs does the opposite of htons.
		printf("Server socket bound to address %s, port %d\n", serverInfo.sockAddr.ipAddr.toString().c_str(), serverInfo.sockAddr.port);
		isRunning = true;
	}
}

ServerConnection::~ServerConnection()
{
}

void ServerConnection::run()
{
	// create a socket address where we will save the data of the socket we receive the message
	// as we want to send a message back to them
	 SockAddr fromToSockAddr;
	 PlayerMessage receivedPlayerMsg;

	// Step 1: //
	// Listen for request of players who want to join a game
	 sf::Packet packet = receiveMessage(&fromToSockAddr);
	 packet >> receivedPlayerMsg;

	// Option 1: There are active games which can host a new player
	if (int(activeGames.size()) > 0 && gameIDCanHost() != -1)
	{
		// Add new player to the host game
		GameInfo* hostGame = &activeGames.at(gameIDCanHost());
		//addNewPlayer(hostGame, from_to_sock_addr);
	}
	// Option 2: There are not active games which can host a new player
	// and the server CAN host a new game
	else if (int(activeGames.size()) < maxNumGames)
	{
		// create a new game
		int newGameId = int(activeGames.size());
		GameInfo newGame;
		newGame.id = newGameId;
		activeGames[newGameId] = newGame;
		// create a new player to that last game created
		//addNewPlayer(&activeGames[newGameId], from_to_sock_addr);
	}
	// Option 2: There are not active games which can host a new player
	// and the server CANNOT host a new game
	else
	{

	}

	// Step 2: //
	// Listen for players which are currently in a active game
	if (int(activeGames.size()) > 0)
	{
		// receive the message of tank x
		//PlayerMessage tank_msg = receiveMessage<PlayerMessage>(&from_to_sock_addr);

		// Update the tank information using the game id and tank id received
		//activeGames[tank_msg.gameId].tanksInfo.at(tank_msg.tankInfo.id) = tank_msg.tankInfo;
		
	}


	// The server first need to receive a message
	//PlayerMessage tank_msg0 = receiveMessage<PlayerMessage>(&from_to_sock_addr);

	// After that send back the message to the sender
	//bool sent = sendMessage<PlayerMessage>(tank_msg0, inet_ntoa(from_to_sock_addr.sin_addr), ntohs(from_to_sock_addr.sin_port));

}

void ServerConnection::addNewPlayer(GameInfo* gameInfo, SockAddr playerSockAddr)
{
	// Step 1:
	// Create Player Id
	// The current number of players will be the player id
	// for example: if there are not player (numPlayers == 0)
	// then the first player id of this game will be 0
	int newPlayerId = gameInfo->numPlayers;

	// Step 2:
	// Add tank info to the collection of that game
	gameInfo->playerInfo.push_back(PlayerInfo());

	// Step 3:
	// Add player sock address to the collection so the server can communicate to them later on
	gameInfo->playersSockAddr.push_back(playerSockAddr);

	// Step 4:
	// Add the player to the game counter
	gameInfo->numPlayers++;
}

int ServerConnection::gameIDCanHost()
{
	for (std::pair<int, GameInfo> game : activeGames)
	{
		// check if that game can host a new player
		if (game.second.numPlayers < maxNumGames)
			return game.first;
	}

	// there are not games which can host a new player
	return -1;
}

GameInfo ServerConnection::getAvailableGame()
{
	for (std::pair<int, GameInfo> game : activeGames)
	{
		// check if that game can host a new player
		if (game.second.numPlayers < maxNumGames)
			return game.second;
	}

	return GameInfo();
}
