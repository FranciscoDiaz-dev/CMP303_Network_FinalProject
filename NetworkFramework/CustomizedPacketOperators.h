#ifndef _CUSTOMIZED_PACKET_OPERATORS_H
#define _CUSTOMIZED_PACKET_OPERATORS_H
#pragma once

#include "PlayerInfo.h"
#include "ConnectionMessage.h"
#include <SFML/Network.hpp>

// Extending packets to handle user types
// It has been used the guide: https://www.sfml-dev.org/tutorials/2.5/network-packet.php

// For Player Info Structure
sf::Packet& operator <<(sf::Packet& packet, const PlayerInfo& tankInfo)
{
	return packet << tankInfo.id << tankInfo.x << tankInfo.y << tankInfo.colour << tankInfo.time;
}

sf::Packet& operator >>(sf::Packet& packet, PlayerInfo& tankInfo)
{
	return packet >> tankInfo.id >> tankInfo.x >> tankInfo.y >> tankInfo.colour >> tankInfo.time;
}

// For Player Message Structure
sf::Packet& operator <<(sf::Packet& packet, const PlayerMessage& tankMsg)
{
	return packet << tankMsg.gameId << tankMsg.playerInfo;
}

sf::Packet& operator >>(sf::Packet& packet, PlayerMessage& tankMsg)
{
	return packet >> tankMsg.gameId >> tankMsg.playerInfo;
}

#endif // _CUSTOMIZED_PACKET_OPERATORS_H