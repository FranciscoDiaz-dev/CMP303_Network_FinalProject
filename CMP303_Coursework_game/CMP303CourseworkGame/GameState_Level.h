// Game State Level
// It is the "real game", where the player/s can play with its/their characters
// Game State Leve extend Game State Base,
// Contains the scenery manager, player manager, camera, parallax manager (System movement).
// @author Francisco Diaz (@FMGameDev)

#ifndef _GAMESTATE_LEVEL_H
#define _GAMESTATE_LEVEL_H
#pragma once

#include "GameStateBase.h"
#include "GameStateManager.h"

class Tank;
class EnemiesManager;

class GameState_Level: public GameStateBase
{
public:
	// Constructor
	GameState_Level(GameStateManager* stateMgr);

	// Destructor
	~GameState_Level();

	// Basic game functions (handleInput, update, render) which are override from Game Sate Base

	// it handle the inputs which are derived to the handleInput function of each manager
	void handleInput(sf::Time dt) override;
	// For update the objects, it derives to manager renders functions
	void update(sf::Time dt) override;
	// For render the objects, it also derives to manager renders functions
	void render() override;

private:
	
	// function to check if it is game over
	// if it is, the level will be added to remove and the game over game state will be displayed
	void goToGameOver();

	// Players
	Tank* player;
	EnemiesManager* enemiesMgr;

	// Floor
	sf::Texture floorTexture;
	sf::Sprite floor;

	float sendUpdateRequestRate;
	float timeSinceLastUpdateRequest;
};

#endif _GAMESTATE_LEVEL_H