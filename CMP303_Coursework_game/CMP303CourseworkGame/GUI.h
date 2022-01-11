#ifndef _GUI_H
#define _GUI_H
#pragma once

// GUI
// Contains the ImGui static functions
// It is used as a way of configurate for this project

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class SharedContext;
class GameStateManager;
class ServersListManager;
class GameState;
class Tank;
class ClientConnection;
class EnemiesManager;


using std::string;
using std::vector;

class GUI
{

public:
	// constructor
	GUI(GameStateManager* gameStateMgr);

	// destructor
	~GUI();

	// process ImGui events
	void processEvent(sf::Event event);
	// update
	void update(sf::Time deltaTime);
	// render
	void render();

	// return the selected server index
	int getSelectedServerIndex() { return selectedServerIndex; };

private:	
	GameStateManager* gameStateMgr;
	sf::RenderWindow* window;
	ServersListManager* serversListMgr;
	ClientConnection* clientConnection;
	Tank* player;
	EnemiesManager* enemiesMgr;
	GameState* gameState;
	int* gameId;
	float* fakeLatency;

	// servers available
	vector<string> serversList;
	int selectedServerIndex;

	// player colours available
	vector<string> playerColours;
	int selectedColourIndex;

	// types of predictions for the enemies
	vector<string> enemyPredictionTypes;
	int selectedPredictionTypeIndex;

	float textTimeout; // seconds
	string timeoutText;
};

#endif //_GUI_H