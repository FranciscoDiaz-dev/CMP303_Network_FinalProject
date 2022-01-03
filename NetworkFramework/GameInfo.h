#ifndef _GAME_INFO_H
#define _GAME_INFO_H
#pragma once

#include <vector>
#include "PlayerInfo.h"
#include "SockAddr.h"

struct GameInfo
{
	// constructor
	GameInfo() : id(-1), numPlayers(-1){}

	// components
	int id; // identifier of this game
	int numPlayers;
	std::vector<PlayerInfo> playerInfo; // information of the tanks of this game
	std::vector<SockAddr> playersSockAddr; // addresses of each player
};

#endif // _GAME_INFO_H
