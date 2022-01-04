#include "ClientConnection.h"
#include "ConnectionMessage.h"

ClientConnection::ClientConnection()
	: ConnectionBase()
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
}

bool ClientConnection::joinAGame(PlayerMessage* playerMsg, SockAddr toSockAddr)
{
	// Sent this player info to the server
	sf::Packet packet;
	packet << playerMsg;
	bool send = ConnectionBase::udpSendMessage(packet, toSockAddr);

	// the player has not join a game yet then listen for the server to be assigned it to a game
	if (send && (*playerMsg).gameId == -1)
	{
		sf::Packet packet2;
		bool received = ConnectionBase::udpReceiveMessage(&packet2, &toSockAddr, sf::seconds(5.0f));

		// if there has been received a message
		if (received)
		{
			// save the data in the struct this game uses
			packet2 >> (*playerMsg);

			// check if has been assigned a game or not
			if ((*playerMsg).gameId != -1) // this mean it has been assigned a new game
			{
				// update the player info;
				printf("Game assigned %d.\n", (*playerMsg).playerInfo.id);
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