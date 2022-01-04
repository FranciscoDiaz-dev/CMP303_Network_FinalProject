#ifndef _GAME_INFO_H
#define _GAME_INFO_H
#pragma once

#include <vector>
#include "PlayerInfo.h"
#include "SockAddr.h"

struct GameInfo
{
	// constructor
	GameInfo() : id(-1), numPlayers(0){}

	// components
	int id; // identifier of this game (if it is -1 means not game has beeen assigned to it yet)
	int numPlayers; // number of players this game currently has
	std::vector<PlayerInfo> playersInfo; // information of the players of this game
	std::vector<SockAddr> playersSockAddr; // addresses of each player
};

#endif // _GAME_INFO_H
