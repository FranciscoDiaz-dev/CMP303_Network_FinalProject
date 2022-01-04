#ifndef _CUSTOMIZED_PACKET_OPERATORS_H
#define _CUSTOMIZED_PACKET_OPERATORS_H
#pragma once

#include "PlayerInfo.h"
#include "ConnectionMessage.h"
#include <SFML/Network.hpp>

// Extending packets to handle user types
// It has been used the guide: https://www.sfml-dev.org/tutorials/2.5/network-packet.php

// For Player Info Structure
sf::Packet& operator <<(sf::Packet& packet, const PlayerInfo& playerInfo)
{
	return packet << playerInfo.id << playerInfo.x << playerInfo.y << playerInfo.colour << playerInfo.time;
}

sf::Packet& operator >>(sf::Packet& packet, PlayerInfo& playerInfo)
{
	return packet >> playerInfo.id >> playerInfo.x >> playerInfo.y >> playerInfo.colour >> playerInfo.time;
}

// For Player Message Structure
sf::Packet& operator <<(sf::Packet& packet, const PlayerMessage& playerMsg)
{
	return packet << playerMsg.gameId << playerMsg.playerInfo;
}

sf::Packet& operator >>(sf::Packet& packet, PlayerMessage& playerMsg)
{
	return packet >> playerMsg.gameId >> playerMsg.playerInfo;
}

#endif // _CUSTOMIZED_PACKET_OPERATORS_H