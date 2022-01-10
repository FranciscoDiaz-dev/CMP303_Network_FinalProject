#include "ConnectionMessage.h"

sf::Packet& operator <<(sf::Packet& packet, const TankInfo& tankInfo)
{
	return packet << tankInfo.id << tankInfo.x << tankInfo.y << tankInfo.colour << tankInfo.isBot << tankInfo.time;
}

sf::Packet& operator >>(sf::Packet& packet, TankInfo& tankInfo)
{
	return packet >> tankInfo.id >> tankInfo.x >> tankInfo.y >> tankInfo.colour >> tankInfo.isBot >> tankInfo.time;
}