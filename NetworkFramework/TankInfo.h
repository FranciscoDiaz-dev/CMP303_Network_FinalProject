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
	TankInfo() : id(-1), x(-1), y(-1), colour(""), time(-1.f) {}
	TankInfo(int identifier) : id(identifier), x(-1), y(-1), colour(""), time(-1.f) {}
	TankInfo(int identifier, float xPos, float yPos, string textureColour, float runTime) :
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
// From tankInfo to Packet
sf::Packet& operator <<(sf::Packet& packet, const TankInfo& tankInfo);
// From Packet to TankInfo
sf::Packet& operator >>(sf::Packet& packet, TankInfo& tankInfo);

// From std::vector<tankInfo> to Packet
// vectors need to be initialised with the num of element to send/receive
sf::Packet& operator <<(sf::Packet& packet, const std::vector<TankInfo>& tanksInfo);
// From Packet to std::vector<tankInfo>
// vectors need to be initialised with the num of element to send/receive
sf::Packet& operator >>(sf::Packet& packet, std::vector<TankInfo>& tanksInfo);

#endif // _PLAYER_INFO_H