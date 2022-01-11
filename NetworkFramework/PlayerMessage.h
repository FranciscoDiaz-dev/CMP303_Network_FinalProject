#ifndef _PLAYER_MESSAGE_H
#define _PLAYER_MESSAGE_H
#pragma once

// Player Message
// It is the type of data the player send to the server (on tcp and udp)
// and this return to them (on tcp)

#include <SFML/Network.hpp>
#include "TankInfo.h"
#include "RequestType.h"
#include "..\CMP303_Coursework_game\CMP303CourseworkGame\GameState.h"


/** A position update message. */
struct PlayerMessage
{
	// constructor
	PlayerMessage() : gameId(-1), requestType(int(RequestType::NONE)), gState(int(GState::SELECTION)), numActiveEnemies(0){}

	// components
	// Identifier of the game this player is from (if it is -1 means not game has beeen assigned to it yet)
	// This id will determ the "map/level/background" for this game
	// It is initialised by the server when a game is created on it.
	int gameId;
	int requestType;
	int gState;
	int numActiveEnemies; // number of enemies which this player/tank has information about
	TankInfo tankInfo;// information of the player
};


// Extending packets to handle user types
// It has been used the guide: https://www.sfml-dev.org/tutorials/2.5/network-packet.php
// 
// For Player Message Structure
sf::Packet& operator <<(sf::Packet& packet, const PlayerMessage& playerMsg);
sf::Packet& operator >>(sf::Packet& packet, PlayerMessage& playerMsg);

#endif //  _PLAYER_MESSAGE_H