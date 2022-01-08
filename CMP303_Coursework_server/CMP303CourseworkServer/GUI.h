#ifndef _GUI_H
#define _GUI_H
#pragma once

#include <vector>
#include <string>
#include <SFML\Graphics.hpp>

#include "SharedContext.h"

class ServersListManager;
class ServerConnection;


using std::string;
using std::vector;

class GUI
{

public:
	// constructor
	GUI(SharedContext* sharedCtxt);

	// destructor
	~GUI();

	// process ImGui events
	void processEvent(sf::Event event);
	// update
	void update(sf::Time deltaTime);
	// render
	void render();


private:

	sf::RenderWindow* window;
	ServersListManager* serversListMgr;
	SharedContext* sharedContext;

	// servers available
	vector<string> servers;
	int selectedServerIndex;
};

#endif //_GUI_H