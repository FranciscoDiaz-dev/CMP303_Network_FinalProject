// Game State JoiningRoom
// It is the "real game", where the player/s can play with its/their characters
// Game State Leve extend Game State Base,
// Contains the scenery manager, player manager, camera, parallax manager (System movement).
// @author Francisco Diaz (@FMGameDev)

#ifndef _GAMESTATE_SELECTION_H
#define _GAMESTATE_SELECTION_H
#pragma once

#include "GameStateBase.h"
#include "GameStateManager.h"
#include "Tank.h"
#include "GUI.h"

#include <vector>

class GameState_Selection : public GameStateBase
{
public:
	// Constructor
	GameState_Selection(GameStateManager* stateMgr);

	// Destructor
	~GameState_Selection();

	// Basic game functions (handleInput, update, render) which are override from Game Sate Base

	// it handle the inputs which are derived to the handleInput function of each manager
	void handleInput(sf::Time dt) override;
	// For update the objects, it derives to manager renders functions
	void update(sf::Time dt) override;
	// For render the objects, it also derives to manager renders functions
	void render() override;

private:
	// This player object
	Tank* player;

	// Text
	sf::Font montserratFont;
	sf::Text infoText;
	sf::Text instructionsText;

	GUI* gui;
};

#endif //_GAMESTATE_SELECTION_H