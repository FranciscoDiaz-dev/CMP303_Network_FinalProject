#ifndef _ENEMY_H
#define _ENEMY_H
#pragma once

#pragma once
#include "Tank.h"

enum class RenderMode {
	REAL_ONLY = 0,
	PREDICTED_ONLY, // rendering only the ghostSprite
	REAL_AND_PREDICTED // rendering the ghostSprite and the real one
};

class Enemy : public Tank
{
public:
	// constructor
	Enemy();
	// destructor
	~Enemy();

	// Handle the input of this tanks
	void HandleInput(float dt) override;
	// Sets the player's position to the latest network position
	void Update(float dt) override;
	//Draw the player / or the ghost / or both
	void Render(sf::RenderWindow* window) override;

	// Use this to set the prediction position
	void setGhostPosition(sf::Vector2f pos);

	// Set the type of rendering
	void SetRenderMode(const RenderMode renderMode) { m_RenderMode = renderMode; };

	// Set the texture(and colour) of this tank (barrel, body and the ghost)
	void SetTexture(std::string colour) override;

	// Add a message to the enemy network message queue
	void SetTankInfo(const TankInfo latestTanksInfo) override;

	// This method calculates and stores the position, but also returns it immediately for use in the main loop
	// This is my where prediction would be... IF I HAD ANY
	sf::Vector2f RunPrediction(float gameTime);

	float getLastInfoTankTime() { return m_Messages.back().time; };

	// Reset all the tank info
	void Reset() override;

private:
	// Component where we will be reading the player stats
	std::vector<TankInfo> m_Messages;

	// Ghost components (predicted object state)//
	// it uses the same texture than this object
	sf::Sprite	m_GhostSprite; // ghost body

	// How this enemy is rendered
	RenderMode	m_RenderMode;
};

#endif

