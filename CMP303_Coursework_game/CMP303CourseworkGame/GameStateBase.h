#ifndef _GAMESTATEBASE_H
#define _GAMESTATEBASE_H
#pragma once

// Game State Base
// All of the game states will extend of Game state Base
// This class has mainly all the game basic functions (handleInput, update and render),  gameStateMgr object
// @author Francisco Diaz (@FMGameDev)

#include <SFML/Graphics.hpp>
#include "SharedContext.h"
#include <string>
#include <iostream>

// We declared class GameStateManager to avoid recursive definitions becase the GameStateManager class header needs to include the GameStateBase class header
// and GameStateBase has a GameStateManager so need to include the class
// IMPORTANT: In each Game state which extends GameStateBase needs to include "GameStateManager.h" to include the real GameStateManager we use
class GameStateManager; 

class GameStateBase {

public:
	//GameStateBase();
	GameStateBase(GameStateManager* stateMgr);
	~GameStateBase();

	// Virtual functions. Base function does nothing (for static objects). Inheritted version will most likely override this function.
	virtual void handleInput(sf::Time dt);
	virtual void update(sf::Time dt);
	virtual void render();

protected:
	// Pointer to the game state manager
	GameStateManager* gameStateMgr;

	// Window component
	sf::RenderWindow* window;
	// Imput component
	Input* input;

	// object to connect to server
	ClientConnection* clientConnection;

	// Text
	sf::Font montserratFont;
	sf::Text titleText; // text of the window/game state
	sf::Text infoText; // text to print any info to the right

	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();
};

#endif _GAMESTATEBASE_H