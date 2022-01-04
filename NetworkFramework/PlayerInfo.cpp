#include "ConnectionMessage.h"

sf::Packet& operator <<(sf::Packet& packet, const PlayerInfo& playerInfo)
{
	return packet << playerInfo.id << playerInfo.x << playerInfo.y << playerInfo.colour << playerInfo.time;
}

sf::Packet& operator >>(sf::Packet& packet, PlayerInfo& playerInfo)
{
	return packet >> playerInfo.id >> playerInfo.x >> playerInfo.y >> playerInfo.colour >> playerInfo.time;
}