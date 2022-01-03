#ifndef _GUI_H
#define _GUI_H
#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "../../NetworkFramework/ServerInfo.h"

class SharedContext;


using std::string;
using std::vector;

class GUI
{

public:
	// constructor
	GUI(sf::RenderWindow* wnd, SharedContext* sharedContxt);

	// destructor
	~GUI();

	// process ImGui events
	void processEvent(sf::Event event);
	// update
	void update(sf::Time deltaTime);
	// render
	void render();

	// Activate ImGui
	void active();
	void deactive();

private:
	bool isActivated;
	sf::RenderWindow* window;

	SharedContext* sharedContext;

	// servers available
	vector<string> servers;
	ServerInfo selectedServerInfo;
	int selectedServerIndex;

	// tank colours available
	vector<string> tankColours;
	int selectedColourIndex = 0;
};

#endif //_GUI_H