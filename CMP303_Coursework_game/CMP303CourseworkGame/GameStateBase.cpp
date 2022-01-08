#include "GameStateBase.h"


// We include the Game State Manager here to avoid the recursive definitions and be available to use the getSharedContext()
#include "GameStateManager.h"  // this "include" needs to be included in each class that extend from GameStateBase (in the.h)

GameStateBase::GameStateBase(GameStateManager* stateMgr) : gameStateMgr(stateMgr)
{
	// get from game state manager the most used components in every game state to avoid large repetitions of code
	window = gameStateMgr->getSharedContext()->window;
	input = gameStateMgr->getSharedContext()->input;
	netSimulator = gameStateMgr->getSharedContext()->netSimulator;
}

GameStateBase::~GameStateBase()
{
}

// override this function to provide functionality
void GameStateBase::handleInput(sf::Time dt)
{
}

// override this function to provide functionality
void GameStateBase::update(sf::Time dt)
{
}

// override this function to provide functionality
void GameStateBase::render()
{
}

// Begins rendering to the back buffer. Background colour set to light blue.
void GameStateBase::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void GameStateBase::endDraw()
{
	window->display();
}