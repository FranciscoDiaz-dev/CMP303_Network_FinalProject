#include "GameStateManager.h"

// Constructor
GameStateManager::GameStateManager(SharedContext* shContext): sharedContext(shContext)
{
	// Register all the game states are availables in this game and with which class are linked/related
	//RegisterState<GameState_MainMenu>(GState::MAIN_MENU);
	RegisterState<GameState_Level>(GState::LEVEL);
	//RegisterState<GameState_GameOver>(GState::GAME_OVER);
}

// Destructor
GameStateManager::~GameStateManager()
{
	// Delete all the states/pointers created in this class
	for (auto& state : stateContainer)
	{
		delete state.second; // delete the game state object created in the function "createState(...)"
	}
}

// Function to switch to another game state
// basically this method look for the game state base object by its game state/name and 
// it emplace it in the back of the state container because the handleInput, update and render in this class
// it uses only the back element in the container
// if there is not any game state created which matches which the parameter passed, then create that game state
void GameStateManager::switchTo(const GState& gState)
{
	sharedContext->gameState->setCurrentState(gState); // Change the current game state name stored 

	for (auto state = stateContainer.begin(); state != stateContainer.end(); state++) //Look for the state to switch in the collection game states
	{
		if (state->first == gState) // If it has been found
		{
			// ge the game state name and the game state object from the container
			GState tmpGState = state->first;
			GameStateBase* tmpState = state->second;
			// erase that element from the state container
			stateContainer.erase(state);

			// and emplace it in the last position of the container
			// this is it made because we will update, render, handle, the last games states object will use the back element in the container
			stateContainer.emplace_back(tmpGState, tmpState);
			return;
		}
	}

	// If the game state wasn't found is because it hasn't created yet
	// then it has to be created
	createState(gState);
}

// Basic game function for calling to the handle input function of the current game state
// this current game state to handle will be always in the last position of the state container
void GameStateManager::handleInput(sf::Time dt)
{
	if (stateContainer.empty()) { return; } // check if there are any game state ocject created in the container

	stateContainer.back().second->handleInput(dt); // handle input of the last element in the container
}

// Basic game function for calling to the update function of the current game state
// this current game state to update will be always in the last position of the state container
void GameStateManager::update(sf::Time dt)
{
	if (stateContainer.empty()) { return; } // check if there are any game state ocject created in the container

	stateContainer.back().second->update(dt); // update the last element in the container
}

// Basic game function for calling to the render function of the current game state
// this current game state to render will be always in the last position of the state container
void GameStateManager::render()
{
	if (stateContainer.empty()) { return; } // check if there are any game state object created in the container

	stateContainer.back().second->render(); // render the last element in the container
}

// Function to get the Shared Context used in the game states
SharedContext* GameStateManager::getSharedContext()
{
	return sharedContext;
}

// Function to add the game state which must 
// be removed into the collection of game states to remove
void GameStateManager::addToRemoveContainer(const GState& gState)
{
	gStateToRemove.push_back(gState);
}

// method to process all the request obtained after a cycle of loop
// in our case we only has to remove all the states called to remove (states in the 'gStateToRemove' componet )
// it can be added as many action as neccessary
void GameStateManager::processRequests()
{
	while (gStateToRemove.begin() != gStateToRemove.end()) // while it exits states to remove
	{
		removeState(*gStateToRemove.begin()); // delete that state
		gStateToRemove.erase(gStateToRemove.begin()); // and erase from the container of games states to remove as it has been already removed
	}
}

// function to remove a game state object by its game state name
void GameStateManager::removeState(const GState& gState)
{
	for (auto state = stateContainer.begin(); state != stateContainer.end(); state++) //Look for the state to remove
	{
		if (state->first == gState) // If it has been found, then remove it
		{
			delete state->second; // detele pointer of the object
			stateContainer.erase(state); // erase from the collection
			return;
		}
	}
}

// function to create a game state object by its game state name
void GameStateManager::createState(const GState& gState)
{
	// check if the game state to create it has been registered in constructor of this class (watching the list of possible states)
	// and it is in the state factory container it it is then the state can be created
	auto newState = stateFactory.find(gState);

	if (newState == stateFactory.end()) // If the state has been not found, then don't continue
	{
		return; // Exit
	}

	// If it was registered then create the state:
	GameStateBase* stateBase; // as all the game state extends from game state base we declare this as pointer

	switch (gState)
	{
	//case(GState::MAIN_MENU):
	//	stateBase = new GameState_MainMenu(this);
	//	break;
	case(GState::LEVEL):
		stateBase = new GameState_Level(this);
		break;
	//case(GState::GAME_OVER):
	//	stateBase = new GameState_GameOver(this);
	//	break;
	default:
		return;
		break;
	}

	// set this game state created in the collection/container of game states
	stateContainer.emplace_back(gState, stateBase);
}