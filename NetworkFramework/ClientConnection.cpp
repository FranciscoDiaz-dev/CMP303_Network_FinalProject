#include "ClientConnection.h"
#include "ConnectionMessage.h"
#include "RequestType.h"

ClientConnection::ClientConnection(Tank* tank, int* currentGameId, GameState* currentGameState)
	: player(tank), gameId(currentGameId), gameState(currentGameState), ConnectionBase()
{
	/*// bind the socket to the ip iddress and the port
	if (socket.bind(sf::Socket::AnyPort, static_cast<sf::IpAddress>("0.0.0.0")) != sf::Socket::Done) // "0.0.0.0" means any ip available
	{
		printf("Server socket bound failed to address %s, port %d\n", sf::IpAddress::getLocalAddress().toString().c_str(), socket.getLocalPort());
	}
	else
	{
		// ntohs does the opposite of htons.
		printf("Server socket bound to address %s, port %d\n", sf::IpAddress::getLocalAddress().toString().c_str(), socket.getLocalPort());
	}*/
}

ClientConnection::~ClientConnection()
{
	exitAGame();
}


bool ClientConnection::joinAGame(ServerInfo newServerInfo)
{
	if (tcpSocket.connect(newServerInfo.ipAddr, newServerInfo.tcpListenerPort) != sf::Socket::Done)
	{
		return false;
	}
	else
	{
		PlayerMessage playerMsg;
		playerMsg.gameId = *gameId;
		playerMsg.requestType = int(RequestType::JOIN);
		playerMsg.gState = int(gameState->getCurrentState());
		playerMsg.tankInfo = player->getTankInfo();

		// Convert this message to sf::packet format and send it
		sf::Packet packetSent, packetReceived;
		packetSent << playerMsg;

		if (ConnectionBase::tcpSendMessage(packetSent, &tcpSocket) && ConnectionBase::tcpReceiveMessage(&packetReceived, tcpSocket, sf::seconds(1.0f)))
		{
			// Save the packet received and check if this player
			// has been assigned a game id
			packetReceived >> playerMsg;
			// If a game has been assigned to the player then update the all player information, game id assigned and server address
			if (playerMsg.gameId != -1) // this mean it has been assigned a new game
			{
				// Update the game id
				*gameId = playerMsg.gameId;
				// Update the player info
				// which contain the new player id, new position etc (assigned by the server)
				player->setTankInfo(playerMsg.tankInfo);

				// Save the server address
				serverInfo = newServerInfo;

				// update the player info;
				printf("Game assigned: %d, player id assigned: %d.\n", playerMsg.gameId, playerMsg.tankInfo.id);

				return true;
			}
			else
			{
				// if we received the -1 game id means that the server didn't received the message or the server is currently busy
				printf("No Game was assigned to this player.\n");
				return false;
			}
		}
	}

	return false;
}

/*
bool ClientConnection::joinAGame(Tank* player, int* gameId, GameState* gameState, ServerInfo newServerInfo)
{
	// Create message with the player and the rest of information to send
	PlayerMessage playerMsg;
	playerMsg.gameId = *gameId;
	playerMsg.requestType = int(RequestType::JOIN);
	playerMsg.gState = int(gameState->getCurrentState());
	playerMsg.tankInfo = player->getTankInfo();

	// Convert this message to sf::packet format and send it
	sf::Packet packetSent, packetReceived;
	packetSent << playerMsg;

	// if it has been sent and this client has been received a response from the server withit 5 seconds
	if(ConnectionBase::udpSendMessage(packetSent, SockAddr(serverInfo.ipAddr, serverInfo.udpPort)) && ConnectionBase::udpReceiveMessage(&packetReceived, &serverSockAddr, sf::seconds(0.1f)))
	{
		// Save the packet received and check if this player
		// has been assigned a game id
		packetReceived >> playerMsg;
		// If a game has been assigned to the player then update the all player information, game id assigned and server address
		if (playerMsg.gameId != -1) // this mean it has been assigned a new game
		{
			// Update the game id
			*gameId = playerMsg.gameId;
			// Update the player info
			// which contain the new player id, new position etc (assigned by the server)
			player->setTankInfo(playerMsg.tankInfo);

			// Save the server address
			serverSocketAddr = serverSockAddr;

			// update the player info;
			printf("Game assigned: %d, player id assigned: %d.\n", playerMsg.gameId, playerMsg.tankInfo.id);

			return true;
		}
		else
		{
			// if we received the -1 game id means that the server didn't received the message or the server is currently busy
			printf("No Game was assigned to this player.\n");
			return false;
		}
		
	}
	return false;
}
*/

bool ClientConnection::exitAGame()
{
	if (tcpSocket.connect(serverInfo.ipAddr, serverInfo.tcpListenerPort) != sf::Socket::Done)
	{
		return false;
	}
	else
	{
		PlayerMessage playerMsg;
		playerMsg.gameId = *gameId;
		playerMsg.requestType = int(RequestType::EXIST);
		playerMsg.gState = int(gameState->getCurrentState());
		playerMsg.tankInfo = player->getTankInfo();

		// Convert this message to sf::packet format and send it
		sf::Packet packetSent, packetReceived;
		packetSent << playerMsg;

		if (ConnectionBase::tcpSendMessage(packetSent, &tcpSocket) && ConnectionBase::tcpReceiveMessage(&packetReceived, tcpSocket, sf::seconds(1.0f)))
		{
			// Save the packet received and check if this player
			// has been assigned a game id
			packetReceived >> playerMsg;

			// If a game has been assigned to the player then update the all player information, game id assigned and server address
			if (playerMsg.requestType == int(RequestType::CONFIRMATION)) // this mean it has been assigned a new game
			{
				printf("Confirmation of Exit.\n");
				return true;
			}
			else
			{
				// if we received the -1 game id means that the server didn't received the message or the server is currently busy
				printf("No confirmation of Exit.\n");
				return false;
			}
		}
	}

	return false;
}

std::vector<TankInfo> ClientConnection::getPlayersInfo(Tank* player, int* gameId, GameState* gameState)
{
	// Create message with the player and the rest of information to send
	PlayerMessage playerMsg;
	playerMsg.gameId = *gameId;
	playerMsg.requestType = int(RequestType::UPDATE);
	playerMsg.gState = int(gameState->getCurrentState());
	playerMsg.tankInfo = player->getTankInfo();

	// Convert this message to sf::packet format and send it
	sf::Packet packetSent, packetReceived;
	packetSent << playerMsg;

	TankInfo playerInfo;
	std::vector<TankInfo> playersInfo;

	SockAddr serverUDPSockAddr(serverInfo.ipAddr, serverInfo.udpPort);

	// if it has been sent and this client has been received a response from the server withit 5 seconds
	if (ConnectionBase::udpSendMessage(packetSent, serverUDPSockAddr) && ConnectionBase::udpReceiveMessage(&packetReceived, &serverUDPSockAddr, sf::seconds(0.1f)))
	{
		while(packetReceived >> playerInfo) // while there is a player to read (save player by player)
		{
			playersInfo.push_back(playerInfo);
		}
	}
	return playersInfo;
}
