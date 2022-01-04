#include "ConnectionMessage.h"

sf::Packet& operator <<(sf::Packet& packet, const PlayerMessage& playerMsg)
{
	return packet << playerMsg.gameId << playerMsg.playerInfo;
}

sf::Packet& operator >>(sf::Packet& packet, PlayerMessage& playerMsg)
{
	return packet >> playerMsg.gameId >> playerMsg.playerInfo;
}