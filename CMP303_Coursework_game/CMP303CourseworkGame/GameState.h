// Game State Class
// Simple game state controller. enum lists possible game states (can be modified), tracks and updates the current state
// @author Paul Robertson
// @modifyBy Francisco Diaz (@FMGameDev)
// - Added new GStates

#pragma once

// Possible states. This enum can be modified to add additional states as required.
enum class GState { SELECTION, WAITING_ROOM, LEVEL, GAME_OVER };

class GameState
{
public:
	// Set the current state
	void setCurrentState(GState s);
	// Returns the current state.
	GState getCurrentState();

protected:
	GState currentState;
};