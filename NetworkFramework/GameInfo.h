#ifndef _GAME_INFO_H
#define _GAME_INFO_H
#pragma once

#include <vector>
#include <utility>
#include "TankInfo.h"
#include "SockAddr.h"

using PlayerData = std::pair<SockAddr, TankInfo>;

struct GameInfo
{
	// constructor
	GameInfo() : id(-1), hasStarted(false), numPlayers(0){}

	// components
	// 
	// Identifier of this game (if it is -1 means not game has beeen assigned to it yet)
	// This id will determ the "map/level/background" for this game
	// It is initialised by the server when a game is created on it.
	int id;
	int numPlayers; // number of players this game currently has
	bool hasStarted;
	std::vector<PlayerData*> playersData; // data of all the players of this game
};

#endif // _GAME_INFO_H
