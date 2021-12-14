// Game State Level
// It is the "real game", where the player/s can play with its/their characters
// Game State Leve extend Game State Base,
// Contains the scenery manager, player manager, camera, parallax manager (System movement).
// @author Francisco Diaz (@FMGameDev)
#pragma once

#include "GameStateBase.h"
#include "GameStateManager.h"
#include "Tank.h"
#include "TankMessage.h"

#include <vector>

class GameState_Level: public GameStateBase
{
public:
	// Constructor
	GameState_Level(GameStateManager* stateMgr);

	// Destructor
	~GameState_Level();

	// Basic game functions (handleInput, update, render) which are override from Game Sate Base

	// it handle the inputs which are derived to the handleInput function of each manager
	void handleInput(float dt) override;
	// For update the objects, it derives to manager renders functions
	void update(float dt) override;
	// For render the objects, it also derives to manager renders functions
	void render() override;

private:
	
	// function to check if it is game over
	// if it is, the level will be added to remove and the game over game state will be displayed
	void goToGameOver();

	// Players
	std::vector<Tank*> tanks;

	// Floor
	sf::Texture floorTexture;
	sf::Sprite floor;

	// Text
	sf::Font montserratFont;
	sf::Text debugText;
};