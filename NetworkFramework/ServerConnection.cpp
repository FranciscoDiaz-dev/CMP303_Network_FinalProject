#include "ServerConnection.h"
#include "ConnectionMessage.h"


ServerConnection::ServerConnection(string serverIdentifier, ServerInfo& serverInfo)
	: serverId(serverIdentifier), maxNumPlayersPerGame(2), maxNumGames(2), ConnectionBase()
{
	// bind the socket to the ip iddress and the port
	if (udpSocket.bind(serverInfo.sockAddr.port, serverInfo.sockAddr.ipAddr) != sf::Socket::Done)
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
	for (GameInfo* gameInfo : activeGames)
	{
		delete gameInfo;
		gameInfo = nullptr;
	}
}

void ServerConnection::run()
{
	// create a socket address where we will save the data of the socket we receive the message
	// as we want to send a message back to them
	 SockAddr fromSockAddr;
	 PlayerMessage receivedPlayerMsg;

	 // Listening the player Message
	 sf::Packet packetReceived;
	 bool msgReceived = udpReceiveMessage(&packetReceived, &fromSockAddr);
	 packetReceived >> receivedPlayerMsg;

	 /* Detect what type of message is*/

	 // Type 1: //
	 // A player who want to join to a game
	 // it will return a gameId equals to -1 (none game was assigned to them)
	 // The server needs to find a game for it if it is possible, if not it will return 
	 if (msgReceived && receivedPlayerMsg.gameId == -1)
	 {

		 printf("Processing request: Join a new game.\n");

		 // There are different results for this request.
		 // Option 1: There are active games which can host a new player
		 if (int(activeGames.size()) > 0 && getAGameIdCanHost() != -1)
		 {
			 printf("Option 1: There are a active game can host.");

			 // Add this new player to a game which is waiting for players
			 // get the game is waiting
			 GameInfo* hostGame = activeGames.at(getAGameIdCanHost()); // get the game which can host
			 // create the player
			 addNewPlayer(hostGame, fromSockAddr, receivedPlayerMsg.playerInfo); // add this player to that game

			 // update the received message player with the game id assigned and their player id
			 receivedPlayerMsg.gameId = hostGame->id;
			 receivedPlayerMsg.playerInfo.id = hostGame->playersInfo.back().id; // last player id added
		 }
		 // Option 2: There are not active games which can host a new player
		 // however the server CAN host a new game
		 else if (int(activeGames.size()) < maxNumGames)
		 {
			 printf("Option 2: There aren't any active game can host, however the server can create a new game.");

			 // Add this player to a new game
			 // create the new game.
			 // the id of the game will be the index position of the vector container
			 activeGames.push_back(new GameInfo());
			 activeGames.back()->id = int(activeGames.size() -1);

			 // create a new player info to that last game created
			 addNewPlayer(activeGames.back(), fromSockAddr, receivedPlayerMsg.playerInfo);

			 // update the received message player with the game id assigned and their player id
			 receivedPlayerMsg.gameId = activeGames.back()->id;
			 receivedPlayerMsg.playerInfo.id = activeGames.back()->playersInfo.back().id; // last player id added
		 }
		 // Option 2: There are not active games which can host a new player
		 // and the server CANNOT host a new game
		 else
		 {
			 printf("Option 3: There aren't any active game can host.");
		 }

		 // sent message with the game and player ids assigned
		 sf::Packet packetSent;
		 packetSent << receivedPlayerMsg;
		 udpSendMessage(packetSent, fromSockAddr);

		 // Wait for confirmation that the player has received their new id
		 // if the confirmation has not been received them remove the player from the game created
		 sf::Packet packetConfirmation;
		 udpReceiveMessage(&packetConfirmation, &fromSockAddr);
		 packetConfirmation >> receivedPlayerMsg;

		 if (receivedPlayerMsg.gameId == -1)
		 {
			 printf("The player did not receive the message.\n");
		 }

	 }
	 // Type 2: //
	 // A Player who is currently in a game
	 //
	 else if (msgReceived)
	 {
		 GameInfo* gameInfo = getGameInfoById(receivedPlayerMsg.gameId);

		 if (gameInfo != nullptr)
		 {
			 // update the player info in the servers if the time in which this information
			 // was sent is later than the one we currently have
			 if (gameInfo->playersInfo.at(receivedPlayerMsg.playerInfo.id).time < receivedPlayerMsg.playerInfo.time)
			 {
				 gameInfo->playersInfo.at(receivedPlayerMsg.playerInfo.id) = receivedPlayerMsg.playerInfo;
			 }

			 // Send to the rest of the players the most updated information of this player
			 for (int i = 0; i < int(gameInfo->playersSockAddr.size()); i++)
			 {
				 if (i != receivedPlayerMsg.playerInfo.id)
				 {
					 sf::Packet packetSent2;
					 packetSent2 << receivedPlayerMsg;
					 udpSendMessage(packetSent2, gameInfo->playersSockAddr.at(i));
				 }
			 }
		 }
		 else
		 {
			 // This game does not exict any more --> 
		 }
	 }

	// Step 2: //
	// Listen for players which are currently in a active game
	if (int(activeGames.size()) > 0)
	{
		// receive the message of player x
		//PlayerMessage player_msg = receiveMessage<PlayerMessage>(&from_to_sock_addr);

		// Update the player information using the game id and player id received
		//activeGames[player_msg.gameId].playersInfo.at(player_msg.playerInfo.id) = player_msg.playerInfo;
		
	}


	// The server first need to receive a message
	//PlayerMessage player_msg0 = receiveMessage<PlayerMessage>(&from_to_sock_addr);

	// After that send back the message to the sender
	//bool sent = sendMessage<PlayerMessage>(player_msg0, inet_ntoa(from_to_sock_addr.sin_addr), ntohs(from_to_sock_addr.sin_port));

}

void ServerConnection::addNewPlayer(GameInfo* gameInfo, SockAddr playerSockAddr, PlayerInfo newPlayerInfo)
{
	// Step 1:
	// Create Player Id
	// The current number of players will be the player id
	// for example: if there are not player (numPlayers == 0)
	// then the first player id of this game will be 0
	newPlayerInfo.id = gameInfo->numPlayers;

	// Step 2:
	// Add player info to the collection of that game
	// The id of this player will be equal to index of this collection where the info of the player is saved
	gameInfo->playersInfo.push_back(newPlayerInfo);

	// Step 3:
	// Add player sock address to the collection so the server can communicate to them later on
	// The id of this player will be equal to index of this collection where the address of the player is saved
	gameInfo->playersSockAddr.push_back(playerSockAddr);

	// Step 4:
	// Add the player to the game counter
	gameInfo->numPlayers++;
}

int ServerConnection::getAGameIdCanHost()
{
	for (int i = 0; i < int(activeGames.size()); i++)
	{
		// check if that game can host a new player
		if (activeGames.at(i)->numPlayers < maxNumGames)
			return i;
	}

	// there are not games which can host a new player
	return -1;
}

GameInfo* ServerConnection::getGameInfoById(int id)
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
