#include "ConnectionBase.h"

ConnectionBase::ConnectionBase()
{
	// Initialise the WinSock library -- we want version 2.2.
	WSADATA w;
	int error = WSAStartup(0x0202, &w);
	if (error != 0)
	{
		die("WSAStartup failed");
	}
	if (w.wVersion != 0x0202)
	{
		die("Wrong WinSock version");
	}

	// Initialise UDP socket.
	sock_ = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_ == INVALID_SOCKET)
	{
		die("socket failed");
	}
}

ConnectionBase::~ConnectionBase()
{
	// We won't actually get here, but if we did then we'd want to clean up...
	printf("Quitting\n");
	closesocket(sock_);
	WSACleanup();
}

bool ConnectionBase::sendMessage(TankMessage tank_msg, std::string to_ip, int to_port)
{
	printf("\nReading from the game object:\n");

	// Fill out a sockaddr_in structure with the address that we want to send to.
	sockaddr_in to_addr;
	to_addr.sin_family = AF_INET;
	to_addr.sin_addr.s_addr = inet_addr(to_ip.c_str());
	// htons converts the port number to network byte order (big-endian).
	to_addr.sin_port = htons(to_port);

	// Send the message to the server.
	if (sendto(sock_, (const char*)&tank_msg, sizeof(TankMessage), 0, (const sockaddr*)&to_addr, sizeof(to_addr)) != sizeof(TankMessage))
	{
		die("sendto failed");
		return false;
	}
	else
	{
		printf("Tank Msg sent: id:%d, x:%d, y:%d.\n", tank_msg.id, tank_msg.x, tank_msg.y);
		return true;
	}
}

TankMessage ConnectionBase::receiveMessage()
{

	sockaddr_in from_addr;
	int from_addr_size = sizeof(from_addr);
	TankMessage tank_msg; // variable where the message will be saved, if it fails, it will return a message with id == -1
	int count = recvfrom(sock_, (char*)&tank_msg, sizeof(TankMessage), 0, (sockaddr*)&from_addr, &from_addr_size);
	if (count < 0)
	{
		die("recvfrom failed");
	}
	else if (count != sizeof(TankMessage))
	{
		die("received odd-sized message");
	}
	else
	{
		printf("Received %d bytes from address %s port %d:\n", count, inet_ntoa(from_addr.sin_addr), ntohs(from_addr.sin_port));
		printf("Msg received: id:%d, x:%d, y:%d.", tank_msg.id, tank_msg.x, tank_msg.y);
		printf("\n");
	}

	return tank_msg;
}


void ConnectionBase::die(const char* message)
{
	fprintf(stderr, "Error: %s (WSAGetLastError() = %d)\n", message, WSAGetLastError());

#ifdef _DEBUG
	// Debug build -- drop the program into the debugger.
	abort();
#else
	exit(1);
#endif
}
