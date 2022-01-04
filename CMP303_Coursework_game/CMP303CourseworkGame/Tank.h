#ifndef _TANK_H
#define _TANK_H
#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include "../../NetworkFramework/PlayerInfo.h"
#include "../../NetworkFramework/ConnectionMessage.h"

enum class RenderMode {
	REAL_ONLY = 0,
	PREDICTED_ONLY,
	REAL_AND_PREDICTED
};


class Tank : public sf::Sprite
{
public:
	Tank();
	~Tank();

	// Sets the player's position to the latest network position
	void Update(float dt);
	//Draw the player / or the ghost / or both
	const void Render(sf::RenderWindow* window);


	// Add a message to the player's network message queue
	void AddMessage(const PlayerInfo& msg);

	// This method calculates and stores the position, but also returns it immediately for use in the main loop
	// This is my where prediction would be... IF I HAD ANY
	sf::Vector2f RunPrediction(float gameTime);

	// Use this to set the prediction position
	void setPosition(float x, float y);
	void setGhostPosition(sf::Vector2f pos);

	void SetRenderMode(const RenderMode renderMode) { m_RenderMode = renderMode; };

	// set the texture/colour of this player
	void SetColour(std::string colour);
	std::string GetColour() { return m_PlayerInfo.colour; };

	PlayerInfo getPlayerInfo()const { return m_PlayerInfo; };
	void setPlayerInfo(PlayerInfo newPlayerInfo) { m_PlayerInfo = newPlayerInfo; };

	void setPlayerId(int id) { m_PlayerInfo.id = id; };

	void Reset();

private:
	// Tank components //
	// Body
	sf::Texture	m_BodyTexture;
	//sf::Sprite is "this" object
	float		m_BodyRotation;
	// Barrel
	sf::Texture m_BarrelTexture;
	sf::Sprite	m_BarrelSprite;
	float		m_BarrelRotation;

	// Name of this player
	PlayerInfo m_PlayerInfo;

	// Ghost components (predicted object state)//
	// it uses the same texture than this object
	sf::Sprite	m_GhostSprite; // ghost body

	// how this player is rendered
	RenderMode	m_RenderMode = RenderMode::REAL_ONLY;

	// Component where we will be reading the player stats
	std::vector<PlayerInfo> m_Messages;
};

#endif //_TANK_H
