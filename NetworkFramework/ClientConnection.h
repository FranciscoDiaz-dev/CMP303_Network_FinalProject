#ifndef _CLIENT_CONNECTION_H
#define _CLIENT_CONNECTION_H
#pragma once

// Client Connection
// It extends from Connection Base
// Add TCP functionality
// It is used for UPD-TCP on the client side

#include <vector>
#include "ConnectionBase.h"
#include "ServerInfo.h"
#include "TankInfo.h"
#include "RequestType.h"

class Tank;
class EnemiesManager;
class GameState;

class ClientConnection : public ConnectionBase
{
public:
	// constructor
	ClientConnection(Tank* tank, EnemiesManager* enemiesManager, int* currentGameId, GameState* currentGameState);
	// destructor
	~ClientConnection();

	// ask the server to join a game, return true if it has joined
	bool joinAGame(ServerInfo newServerInfo);

	// inform the server this player wants to exit the game
	bool exitTheGame();

	// return the lastest players information saved/received on the server
	bool sendThisPlayerInfoToServer();

	// check if the server has sent the enemies info using udp
	// if so update it (only if the receievd are the most updated we got)
	// return true they have received
	bool getEnemiesInfos(float dt);

	int getFakeLatency()const { return fakeLatency; };
	void setFakeLatency(int latency) { fakeLatency = latency; }

	void reset();

private:
	ServerInfo serverInfo; // server information
	sf::TcpSocket tcpSocket; // client socket

	Tank* player;
	EnemiesManager* enemiesMgr;
	int* gameId;
	GameState* gameState;

	// variable to control the udp on client side (first filter)
	float lastTankInfoTimeReceived;
	int fakeLatency; // ms  - fake latency when the player is sending an update tank info to the server
};

#endif // _CLIENT_CONNECTION_H