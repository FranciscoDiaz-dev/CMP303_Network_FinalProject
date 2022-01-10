// Game State Manager
// The function of Game State Manager is manage all the game states (splash, menus, levels, credits, etc), create them, delete them switch to other game state,
// It has a collection with game states, a shared context, etc
// @adapted by Francisco Diaz (@FMGameDev)
// @references:
//		@book: "SFML game development by example create and develop exciting games from start to finish using SFML"
//		@isbn:  ISBN: 9781785287343
//		@editorial: Packt Publishing Ltd.
//		@author: Raimondas Pupius
//		@chapter: "Chapter 5. Can I Pause this? - Application states"
//		@pages: 98-105 
//		I have used it as reference how to create this class for the following methods and components:  
//			- switchTo(), addToRemoveContainer(), processRequests(), createState(...), removeState(...), RegisterState(...)
//			- sharedContext, stateContainer, gStateToRemove and stateFactory.
//		Some parts of them have been modifed to adapt the solution to my game, removing some parts as activate/desactivate state, 
//      the shared context is also used the different way.

#pragma once
#include "SharedContext.h"
#include "GameState.h"

// game state base
#include "GameStateBase.h"

// all the game states of this game
#include "GameState_Level.h"
#include "GameState_Selection.h"

// includes for using in the containers
#include <unordered_map>
#include <vector>
#include <functional>

class GameStateManager
{
public:
	// Constructor
	GameStateManager(SharedContext* sharedContext);

	// Destructor
	~GameStateManager();

	// Function to switch to another game state
	// basically this method look for the game state base object by its game state/name and 
	// it emplace it in the back of the state container because the handleInput, update and render in this class
	// it uses only the back element in the container
	// if there is not any game state created which matches which the parameter passed, then create that game state
	void switchTo(const GState& gState);

	// Basic game function for calling to the update, handle and render function of the current game state
	// this current game state will be always in the last position of the state container
	void handleInput(sf::Time dt);
	void update(sf::Time dt);
	void render();

	// Function to get the Shared Context used in the game states
	SharedContext* getSharedContext();

	// Function to add the game state which must be
	// removed intto the collection of game states to remove
	void addToRemoveContainer(const GState& gState);

	// method to process all the request obtained after a cycle of loop
	// in our case we only has to remove all the states called to remove (states in the 'gStateToRemove' componet )
	// it can be added any action as it is neccessary
	void processRequests();


private:

	// Shared Context pointer with all the objects which need the game states
	// this shared context will contain pointers such as window, input, player manager, etc
	SharedContext* sharedContext;

	// container with all the game states objects created
	// it is linked/pair to the game state name (gstate)
	// by doing this we could find the game state object by his Game State name linked
	using StateContainer = std::vector<std::pair<GState,GameStateBase*>>;
	StateContainer stateContainer;

	// container with all the game states to remove
	// (it save their game states names, for later looking for them by his linked GState in the stateContainer)
	using GStateContainer = std::vector<GState>;
	GStateContainer gStateToRemove;

	// map that links a game state name/type to a std::function type
	// this is allowed predefine the game state class which an game state name will be linked
	using StateFactory = std::unordered_map<GState, std::function<GameStateBase* (void) >>;
	StateFactory stateFactory;

	// use of lambda expression:
	// this maps the gState in the stateFactory map to a function which returns
	// a pointer to the newly allocated memory.
	template<class T>
	void RegisterState(const GState& gState)
	{
		stateFactory[gState] = [this]()->GameStateBase*
		{
			return new T(this);
		};
	}

	// function to remove a game state object by its game state name
	void removeState(const GState& gState);

	// function to create a game state object by its game state name
	void createState(const GState& gState);
};

