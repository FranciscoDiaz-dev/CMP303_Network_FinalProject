#ifndef _GAMESTATE_SELECTION_H
#define _GAMESTATE_SELECTION_H
#pragma once

// Game State Selection
// It is the "real game", where the player/s can play with its/their characters
// Game State Leve extend Game State Base,
// Contains the scenery manager, player manager, camera, parallax manager (System movement).
// @author Francisco Diaz (@FMGameDev)

#include <vector>
#include "GameStateBase.h"
#include "GameStateManager.h"

class Tank;
class GUI;

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
	sf::Text infoText;

	// Gui which is used as the menu for this network game
	GUI* gui;
};

#endif //_GAMESTATE_SELECTION_H