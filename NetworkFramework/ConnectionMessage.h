#ifndef _CONNECTION_MESSAGE_H
#define _CONNECTION_MESSAGE_H
#pragma once

#include <SFML/Network.hpp>
#include "PlayerInfo.h"

/** A position update message. */
struct PlayerMessage
{
	// constructor
	PlayerMessage() : gameId(-1) {}

	// components
	int gameId;// identifier of the game this tank is from 
	PlayerInfo playerInfo;// information of the tank
};

#endif //  _CONNECTION_MESSAGE_H