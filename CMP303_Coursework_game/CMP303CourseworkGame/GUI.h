#ifndef _GUI_H
#define _GUI_H
#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class SharedContext;
class GameStateManager;
class ServersManager;
class Tank;
class ClientConnection;


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

private:	
	GameStateManager* gameStateMgr;
	sf::RenderWindow* window;
	ServersManager* serversMgr;
	ClientConnection* clientConnection;
	Tank* player;
	int* gameId;

	// servers available
	vector<string> servers;
	int selectedServerIndex;

	// player colours available
	vector<string> playerColours;
	int selectedColourIndex;
};

#endif //_GUI_H