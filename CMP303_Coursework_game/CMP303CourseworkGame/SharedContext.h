#ifndef _SHARED_CONTEXT_H
#define _SHARED_CONTEXT_H
#pragma once

// Shared Context
// it is an unique file 
// Shared Context contains two structures with all the pointers to the objects which are necessary in all the game (every game states)
// This pointers will be pointing to the objects which must be declared in some static class which will be active during all the game
// In this case these objects has been created in the main.cpp
// @author Francisco Diaz (@FMGameDev)
// @references:
//		@book: "SFML game development by example create and develop exciting games from start to finish using SFML"
//		@isbn:  ISBN: 9781785287343
//		@editorial: Packt Publishing Ltd.
//		@author: Raimondas Pupius
//		@chapter: "Chapter 5. Can I Pause this? - Application states"
//		@page: 98
//		I have used it as reference how to create a structure (sharedContext) where has pointer to every component used in all the game.



// All the components that are shared between the game states
// They must been initialise in the Game App or any of the mains

class Input;
class NetworkSimulator;
class GameState;
class GUI;
class Tank;
class ServersManager;
class ClientConnection;

namespace sf
{
	class String;
	class RenderWindow;
}

struct SharedContext
{
	// constructor
	SharedContext() : kGameName(nullptr), kMinWindowWith(nullptr), kMinWindowHeight(nullptr),
		window(nullptr), input(nullptr), serversManager(nullptr), player(nullptr), netSimulator(nullptr), gameState(nullptr), clientConnection(nullptr), gameId(nullptr), gui(nullptr){}

	// components
	const sf::String* kGameName; // name of the game, used in the window game
	const unsigned int* kMinWindowWith;
	const unsigned int* kMinWindowHeight;
	sf::RenderWindow* window; // window component
	Input* input; // imput component
	NetworkSimulator* netSimulator;
	ServersManager* serversManager;
	ClientConnection* clientConnection;
	Tank* player;
	GameState* gameState; // game state component which contains the current game state
	int* gameId;
	GUI* gui;
};

#endif // _SHARED_CONTEXT_H