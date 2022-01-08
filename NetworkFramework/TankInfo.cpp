#include "ConnectionMessage.h"

sf::Packet& operator <<(sf::Packet& packet, const TankInfo& tankInfo)
{
	return packet << tankInfo.id << tankInfo.x << tankInfo.y << tankInfo.colour << tankInfo.time;
}

sf::Packet& operator >>(sf::Packet& packet, TankInfo& tankInfo)
{
	return packet >> tankInfo.id >> tankInfo.x >> tankInfo.y >> tankInfo.colour >> tankInfo.time;
}


sf::Packet& operator <<(sf::Packet& packet, const std::vector<TankInfo>& tanksInfo)
{
	for (TankInfo tankInfo : tanksInfo)
	{
		packet << tankInfo.id << tankInfo.x << tankInfo.y << tankInfo.colour << tankInfo.time;
	}

	return packet;
}

sf::Packet& operator >>(sf::Packet& packet, std::vector<TankInfo>& tanksInfo)
{
	for (TankInfo tankInfo : tanksInfo)
	{
		packet >> tankInfo.id >> tankInfo.x >> tankInfo.y >> tankInfo.colour >> tankInfo.time;
	}

	return packet;
}