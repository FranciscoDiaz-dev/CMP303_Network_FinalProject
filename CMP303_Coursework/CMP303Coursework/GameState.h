// Game State Class
// Simple game state controller. enum lists possible game states (can be modified), tracks and updates the current state
// @author Paul Robertson
// @modifyBy Francisco Diaz (@FMGameDev)
// - Added new GStates

#pragma once

// Possible states. This enum can be modified to add additional states as required.
enum class GState { SPLASH, MAIN_MENU, DIFFICULTY_SELECTION, SCENARY_MENU, CHARACTER_MENU, CONTROLS, LEVEL, PAUSED, GAME_OVER, ABOUT, CREDITS };

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