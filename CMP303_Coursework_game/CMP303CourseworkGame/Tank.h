#ifndef _TANK_H
#define _TANK_H
#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include "../../NetworkFramework/TankInfo.h"
#include "../../NetworkFramework/ConnectionMessage.h"


class Tank : public sf::Sprite
{
public:
	// Constructor
	Tank();
	// Destructor
	~Tank();

	// Handle the input of this tanks
	virtual void HandleInput(float dt);
	// Sets the player's position to the latest network position
	virtual void Update(float dt);
	//Draw the player / or the ghost / or both
	virtual void Render(sf::RenderWindow* window);

	// Set the Position of this tank (body and barrel)
	void SetPosition(sf::Vector2f pos);

	// Return the tank info of this tank
	TankInfo getTankInfo()const { return m_TankInfo; };
	// Set the Tank info of this tank
	void setTankInfo(TankInfo newTankInfo);

	// Set the texture(and colour) of this tank (barrel and body)
	virtual void SetTexture(std::string colour);
	// Get the colour of this player
	std::string GetColour() { return m_TankInfo.colour; };

	// Set this tank id
	void SetId(int id) { m_TankInfo.id = id; };
	// Return this tank id
	int GetId() { return m_TankInfo.id; };

	// Reset all the tank info
	virtual void Reset();

protected:
	// Tank components //
	// Body
	sf::Texture	m_BodyTexture;
	//sf::Sprite is "this" object
	float m_BodyRotation;
	// Barrel
	sf::Texture m_BarrelTexture;
	sf::Sprite m_BarrelSprite;
	float m_BarrelRotation;

	// Tank information used for rendering, network, etc
	TankInfo m_TankInfo;
};

#endif //_TANK_H
