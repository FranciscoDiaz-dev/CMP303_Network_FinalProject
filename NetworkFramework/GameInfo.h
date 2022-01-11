#ifndef _GAME_INFO_H
#define _GAME_INFO_H
#pragma once

// Game Info
// It is the structure used by the server for saving all the data of each game

#include <vector>
#include <utility>
#include "TankInfo.h"
#include "SockAddr.h"

using PlayerData = std::pair<SockAddr, TankInfo>;

struct GameInfo
{
	// constructor
	GameInfo() : id(-1), hasStarted(false), nextTankId(0), numPlayers(0){}
	GameInfo(int identifier) : id(identifier), hasStarted(false), nextTankId(0), numPlayers(0) {}

	// Components
	// 
	// Identifier of this game (if it is -1 means not game has beeen assigned to it yet)
	// This id will determ the "map/level/background" for this game
	// it is initialised by the server when a game is created on it.
	int id;
	int numPlayers; // number of players this game currently has
	bool hasStarted;
	int nextTankId; // it is used for generating tank/player ids
	std::vector<PlayerData*> playersData; // data of all the players of this game
};

#endif // _GAME_INFO_H
