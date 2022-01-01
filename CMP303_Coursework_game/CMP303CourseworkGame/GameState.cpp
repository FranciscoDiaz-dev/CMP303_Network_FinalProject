#include "GameState.h"

// Set the current state
void GameState::setCurrentState(GState s)
{
	currentState = s;
}

// Returns the current state.
GState GameState::getCurrentState()
{
	return currentState;
}