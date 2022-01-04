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
	int gameId;// identifier of the game this player is from 
	PlayerInfo playerInfo;// information of the player
};


// Extending packets to handle user types
// It has been used the guide: https://www.sfml-dev.org/tutorials/2.5/network-packet.php
// 
// For Player Message Structure
sf::Packet& operator <<(sf::Packet& packet, const PlayerMessage& playerMsg);
sf::Packet& operator >>(sf::Packet& packet, PlayerMessage& playerMsg);

#endif //  _CONNECTION_MESSAGE_H