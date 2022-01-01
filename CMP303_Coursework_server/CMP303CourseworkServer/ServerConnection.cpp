#include "ServerConnection.h"

ServerConnection::ServerConnection(std::string server_ip, int server_port)
	: ConnectionBase()
{
	// Fill out a sockaddr_in structure to describe the address we'll listen on.
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
	// htons converts the port number to network byte order (big-endian).
	server_addr.sin_port = htons(server_port);

	// Bind the socket to that address.
	if (bind(sock_, (const sockaddr*)&server_addr, sizeof(server_addr)) != 0)
	{
		die("bind failed");
	}

	// ntohs does the opposite of htons.
	printf("Server socket bound to address %s, port %d\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));
}

ServerConnection::~ServerConnection()
{
}

void ServerConnection::run(std::string to_ip, int to_port)
{
	do
	{
		// The server first need to receive a message
		TankMessage tank_msg = receiveMessage();

		// After that send back the message to the sender
		sendMessage(tank_msg, to_ip, to_port);

	// Keep going until we get a message starting with "quit".
	} while (true);
}
