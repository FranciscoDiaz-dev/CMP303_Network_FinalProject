#ifndef _PLAYER_INFO_H
#define _PLAYER_INFO_H
#pragma once

#include <SFML/Network.hpp>
#include <string>

using std::string;

struct PlayerInfo
{
	// constructors	
	PlayerInfo() : id(-1), x(-1), y(-1), colour(""), time(-1.f) {}
	PlayerInfo(int identifier) : id(identifier), x(-1), y(-1), colour(""), time(-1.f) {}
	PlayerInfo(int identifier, float xPos, float yPos, string textureColour, float runTime) :
		id(identifier), x(xPos), y(yPos), colour(textureColour), time(runTime) {}

	// components

	/** The object number of this player within the game world. */
	int id;

	/** The coordinates of this player within the game world. */
	float x, y;

	// colour
	string colour;

	/** The time at which this info was collected and/or message was sent
	(Not the time at which it was received!) */
	float time;
};

// Extending packets to handle user types
// It has been used the guide: https://www.sfml-dev.org/tutorials/2.5/network-packet.php
//
// For Player Info Structure
sf::Packet& operator <<(sf::Packet& packet, const PlayerInfo& playerInfo);
sf::Packet& operator >>(sf::Packet& packet, PlayerInfo& playerInfo);

#endif // _PLAYER_INFO_H