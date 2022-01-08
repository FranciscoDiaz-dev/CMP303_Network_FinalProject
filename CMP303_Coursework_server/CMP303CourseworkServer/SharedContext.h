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
class GUI;
class ServersListManager;
class ServerConnection;

namespace sf
{
	class String;
	class RenderWindow;
	class Text;
}

struct SharedContext
{
	// constructor
	SharedContext() : kWindowName(nullptr), kMinWindowWith(nullptr), kMinWindowHeight(nullptr),
		window(nullptr), input(nullptr), serversListMgr(nullptr), serverConnection(nullptr), debugText(nullptr), gui(nullptr){}

	// components
	const sf::String* kWindowName; // name of the game, used in the window game
	const unsigned int* kMinWindowWith;
	const unsigned int* kMinWindowHeight;
	sf::RenderWindow* window; // window component
	Input* input; // imput component
	ServersListManager* serversListMgr;
	ServerConnection* serverConnection;
	sf::Text* debugText;
	GUI* gui;
};

#endif // _SHARED_CONTEXT_H