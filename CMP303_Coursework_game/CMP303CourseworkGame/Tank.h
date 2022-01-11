#ifndef _TANK_H
#define _TANK_H
#pragma once

// Tank
// It is the player object
// It contains a tank info object which is used for the messages to the server

#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include "../../NetworkFramework/TankInfo.h"
#include "../../NetworkFramework/PlayerMessage.h"


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
	TankInfo GetTankInfo()const { return m_TankInfo; };
	// Set the Tank info of this tank
	virtual void SetTankInfo(TankInfo newTankInfo);

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

	string GetName()const { return m_TankInfo.name; };
	void SetName(string playerName) { m_TankInfo.name = playerName; m_TankNameText.setString(m_TankInfo.name);};

	// get speed of this tank
	float GetSpeed() { return m_Speed; }
	// set speed of this tank
	void SetSpeed(float speed) { m_Speed = speed; }

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
	float m_Speed;

	// Text and font to show the identifier and score of this tank on screen
	sf::Text m_TankNameText, m_TankScoreText;
	sf::Font m_MontserratFont;
};

#endif //_TANK_H
