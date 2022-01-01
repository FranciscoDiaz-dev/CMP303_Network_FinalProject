#include "ClientConnection.h"

ClientConnection::ClientConnection()
	: ConnectionBase()
{
}

ClientConnection::~ClientConnection()
{
}

void ClientConnection::run(TankMessage tank_msg, std::string to_ip, int to_port)
{
	do
	{
		// The client need first to send a message
		sendMessage(tank_msg, to_ip, to_port);

		// read the response back
		TankMessage tank_msg_response = receiveMessage();

		// Keep going until we get a message starting with "quit".
	} while (true);
}
