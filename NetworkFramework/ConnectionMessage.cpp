#include "ConnectionMessage.h"

sf::Packet& operator <<(sf::Packet& packet, const PlayerMessage& playerMsg)
{
	return packet << playerMsg.gameId << playerMsg.requestType << playerMsg.gState << playerMsg.numActiveEnemies << playerMsg.tankInfo;
}

sf::Packet& operator >>(sf::Packet& packet, PlayerMessage& playerMsg)
{
	return packet >> playerMsg.gameId >> playerMsg.requestType >> playerMsg.gState >> playerMsg.numActiveEnemies >> playerMsg.tankInfo;
}