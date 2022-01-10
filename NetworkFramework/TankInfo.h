#ifndef _PLAYER_INFO_H
#define _PLAYER_INFO_H
#pragma once

#include <SFML/Network.hpp>
#include <string>
#include <vector>

using std::string;

struct TankInfo
{
	// constructors	
	TankInfo() : id(-1), x(0), y(0), colour(""), isBot(false), time(-1.f) {}
	TankInfo(int identifier) : id(identifier), x(0), y(0), colour(""), isBot(false), time(-1.f) {}
	TankInfo(int identifier, float xPos, float yPos, string textureColour, bool bot, float runTime) :
		id(identifier), x(xPos), y(yPos), colour(textureColour), isBot(bot), time(runTime) {}

	// components

	/** The object number of this player within the game world. */
	int id;

	/** The coordinates of this player within the game world. */
	float x, y;

	// colour
	string colour;

	// This tank is a bot (it is not controlled by a machine
	bool isBot;

	/** The time at which this info was collected and/or message was sent
	(Not the time at which it was received!) */
	float time;
};

// Extending packets to handle user types
// It has been used the guide: https://www.sfml-dev.org/tutorials/2.5/network-packet.php
//
// For Player Info Structure
// From tankInfo to Packet
sf::Packet& operator <<(sf::Packet& packet, const TankInfo& tankInfo);
// From Packet to TankInfo
sf::Packet& operator >>(sf::Packet& packet, TankInfo& tankInfo);

#endif // _PLAYER_INFO_H