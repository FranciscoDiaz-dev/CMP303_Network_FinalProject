#ifndef _GUI_H
#define _GUI_H
#pragma once

#include <SFML/Graphics.hpp>
#include "SharedContext.h"

class GUI
{

public:
	// constructor
	GUI(sf::RenderWindow* wnd);

	// destructor
	~GUI();

	void processEvent(sf::Event event);
	void update(sf::Time deltaTime);
	void render();

	void active();
	void deactive();

private:
	bool isActivated;
	sf::RenderWindow* window;

	char windowTitle[255] = "ImGui + SFML = <3";
	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };
};

#endif //_GUI_H