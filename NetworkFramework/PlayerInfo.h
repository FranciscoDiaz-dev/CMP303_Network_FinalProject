#ifndef _PLAYER_INFO_H
#define _PLAYER_INFO_H
#pragma once

#include <string>
using std::string;

struct PlayerInfo
{
	/** The object number of this tank within the game world. */
	int id;

	/** The coordinates of this tank within the game world. */
	float x, y;

	// colour
	std::string colour;

	/** The time at which this info was collected and/or message was sent
	(Not the time at which it was received!) */
	float time;
};

#endif // _PLAYER_INFO_H