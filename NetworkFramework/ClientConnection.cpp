#include "ClientConnection.h"
#include "ConnectionMessage.h"
#include "RequestType.h"

#include "../CMP303_Coursework_game/CMP303CourseworkGame/EnemiesManager.h"
#include "../CMP303_Coursework_game/CMP303CourseworkGame/Tank.h"
#include "../CMP303_Coursework_game/CMP303CourseworkGame/Framework/Vector.h"

ClientConnection::ClientConnection(Tank* tank, EnemiesManager* enemiesManager, int* currentGameId, GameState* currentGameState)
	: player(tank), enemiesMgr(enemiesManager), gameId(currentGameId), gameState(currentGameState), ConnectionBase()
{
	udpSocket.setBlocking(false);
}

ClientConnection::~ClientConnection()
{
	// if the player is in a game then exist
	// in case the player close the windowsetc
	if (*gameId != -1)
		exitTheGame();
}


bool ClientConnection::joinAGame(ServerInfo newServerInfo)
{
	// Try to connect to the server
	sf::Socket::Status socketStatus = tcpSocket.connect(newServerInfo.ipAddr, newServerInfo.tcpListenerPort);

	if (socketStatus == sf::Socket::Done)
	{
		printf("TCP Connected to server with ip:%s and port:%d.\n", newServerInfo.ipAddr.toString().c_str(), int(newServerInfo.tcpListenerPort));

		// Connection to the server sucessfully
		PlayerMessage playerMsgSent;
		playerMsgSent.gameId = *gameId;
		playerMsgSent.requestType = int(RequestType::JOIN);
		playerMsgSent.gState = int(gameState->getCurrentState());
		playerMsgSent.tankInfo = player->GetTankInfo();

		// Convert this message to sf::packet format and send it
		sf::Packet packetSent, packetReceived;
		packetSent << playerMsgSent;

		// add this server tcp socket to the selector
		selector.add(tcpSocket);

		if (ConnectionBase::tcpSendMessage(packetSent, tcpSocket) && ConnectionBase::tcpReceiveMessage(&packetReceived, tcpSocket, false, sf::Time::Zero))
		{
			// Save the packet received into a player message structure
			PlayerMessage playerMsgReceived;
			packetReceived >> playerMsgReceived;

			// If a game has been assigned to the player then update the all player information, game id assigned and server address
			if (playerMsgReceived.requestType == int(RequestType::CONFIRMATION)) // this mean the server has processed the request, thus the player was added to a new game
			{
				// Update the game id
				*gameId = playerMsgReceived.gameId;
				// Update the player info
				// which contain the new player id, new position etc (assigned by the server)
				player->SetTankInfo(playerMsgReceived.tankInfo);

				// Save the server address
				serverInfo = newServerInfo;

				// print info
				printf("\tGame assigned: %d, player id assigned: %d.\n", playerMsgReceived.gameId, playerMsgReceived.tankInfo.id);

				return true;
			}
		}
	}
	else
	{
		// it has not been possible connect to the server
		printf("TCP Server with ip:%s and port:%d not reacheable.\n", newServerInfo.ipAddr.toString().c_str(), int(newServerInfo.tcpListenerPort));
		return false;
	}

	// The server is currently busy or the server cannot host more players/games
	printf("\tNo Game was assigned to this player.\n");
	return false;
}

bool ClientConnection::exitTheGame()
{
	sf::Socket::Status socketStatus = tcpSocket.connect(serverInfo.ipAddr, serverInfo.tcpListenerPort);

	// if the connection was successfull
	if(socketStatus == sf::Socket::Done)
	{
		printf("TCP Connected to server with ip:%s and port:%d.\n", serverInfo.ipAddr.toString().c_str(), int(serverInfo.tcpListenerPort));

		PlayerMessage playerMsgSent;
		playerMsgSent.gameId = *gameId;
		playerMsgSent.requestType = int(RequestType::EXIT);
		playerMsgSent.gState = int(gameState->getCurrentState());
		playerMsgSent.tankInfo = player->GetTankInfo();

		// Convert this message to sf::packet format and send it
		sf::Packet packetSent, packetReceived;
		packetSent << playerMsgSent;

		if (ConnectionBase::tcpSendMessage(packetSent, tcpSocket) && ConnectionBase::tcpReceiveMessage(&packetReceived, tcpSocket, false, sf::Time::Zero))
		{
			// Save the packet received into a player message structure
			PlayerMessage playerMsgReceived;
			packetReceived >> playerMsgReceived;

			if (playerMsgReceived.requestType == int(RequestType::CONFIRMATION)) // this mean the server has processed the request, thus the player was deleted form the server
			{
				printf("\tConfirmation of Exit.\n");

				// Reset the game id to the one received by the server
				*gameId = -1;

				// set this socket is not going to be used at the moment
				// thus remove it from the selector notifications
				selector.remove(tcpSocket);

				return true;
			}
		}
	}
	else
	{
		// it has not been possible connect to the server
		printf("TCP Server with ip:%s and port:%d not reacheable.\n", serverInfo.ipAddr.toString().c_str(), int(serverInfo.tcpListenerPort));
		return false;
	}

	printf("\tNo confirmation of Exit.\n");
	return false;
}

bool ClientConnection::sendThisPlayerInfoToServer()
{
	// Create message with the player and the rest of information to send
	PlayerMessage playerMsgSent;
	playerMsgSent.gameId = *gameId;
	playerMsgSent.requestType = int(RequestType::UPDATE);
	playerMsgSent.gState = int(gameState->getCurrentState());
	playerMsgSent.numActiveEnemies = enemiesMgr->getNumActiveEnemies();
	playerMsgSent.tankInfo = player->GetTankInfo();

	// Convert this message to sf::packet format and send it
	sf::Packet packetSent;
	packetSent << playerMsgSent;

	// create the objects where the player infos will be saved
	TankInfo tankInfoReceived;
	std::vector<TankInfo> tanksInfoReceived;

	// The server socket address, and the object where the server address response will be saved
	SockAddr serverUDPSockAddr(serverInfo.ipAddr, serverInfo.udpPort);

	// if it has been sent and this client has been received a response from the server then update the player info and enemies info
	if (ConnectionBase::udpSendMessage(packetSent, serverUDPSockAddr))
		return true;
	else
		return false;
}

std::vector<TankInfo> ClientConnection::getEnemiesInfos()
{ 
	// create the objects where the player infos will be saved
	sf::Packet packetReceived;
	TankInfo tankInfoReceived;
	std::vector<TankInfo> tanksInfoReceived;

	// The server socket address, and the object where the server address response will be saved
	SockAddr fromUDPSockAddr;

	// if it has been sent and this client has been received a response from the server then update the player info and enemies info
	if (ConnectionBase::udpReceiveMessage(&packetReceived, &fromUDPSockAddr, true))
	{
		while (packetReceived >> tankInfoReceived) // while there is a player to read (save player info by player info)
		{
			tanksInfoReceived.push_back(tankInfoReceived);
		}

		// remove this player from the list
		if(!tanksInfoReceived.empty())
			tanksInfoReceived.erase(tanksInfoReceived.begin() + player->GetId()); // remove this player from the collection
	}

	return tanksInfoReceived;
}
