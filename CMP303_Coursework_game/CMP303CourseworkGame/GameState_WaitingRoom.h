// Game State WaitingRoom
// It is the "real game", where the player/s can play with its/their characters
// Game State Leve extend Game State Base,
// Contains the scenery manager, player manager, camera, parallax manager (System movement).
// @author Francisco Diaz (@FMGameDev)

#ifndef _GAMESTATE_WAIITNG_ROOM_H
#define _GAMESTATE_WAIITNG_ROOM_H
#pragma once

#include "GameStateBase.h"
#include "GameStateManager.h"
#include "Tank.h"
#include "EnemiesManager.h"
#include "..\..\NetworkFramework\ClientConnection.h"

#include <vector>

class GameState_WaitingRoom : public GameStateBase
{
public:
	// Constructor
	GameState_WaitingRoom(GameStateManager* stateMgr);

	// Destructor
	~GameState_WaitingRoom();

	// Basic game functions (handleInput, update, render) which are override from Game Sate Base

	// it handle the inputs which are derived to the handleInput function of each manager
	void handleInput(sf::Time dt) override;
	// For update the objects, it derives to manager renders functions
	void update(sf::Time dt) override;
	// For render the objects, it also derives to manager renders functions
	void render() override;

private:
	// Players
	Tank* player;
	EnemiesManager* enemiesMgr;

	// Text
	sf::Font montserratFont;
	sf::Text titleText;
	sf::Text infoText;

	ClientConnection* clientConnection;
	GameState* gameState;
	int* gameId;
};

#endif //_GAMESTATE_WAIITNG_ROOM_H
