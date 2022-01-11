#include "TankInfo.h"

sf::Packet& operator <<(sf::Packet& packet, const TankInfo& tankInfo)
{
	return packet << tankInfo.name << tankInfo.id << tankInfo.x << tankInfo.y << tankInfo.colour << tankInfo.time;
}

sf::Packet& operator >>(sf::Packet& packet, TankInfo& tankInfo)
{
	return packet >> tankInfo.name >> tankInfo.id >> tankInfo.x >> tankInfo.y >> tankInfo.colour >> tankInfo.time;
}