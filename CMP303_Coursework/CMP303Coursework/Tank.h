#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "TankMessage.h"

class Tank : public sf::Sprite
{
public:
	Tank(std::string color);
	~Tank();

	enum RenderMode {
		REAL_ONLY,
		PREDICTED_ONLY,
		REAL_AND_PREDICTED
	};

	void Update(float dt);
	const void Render(sf::RenderWindow* window);

	void AddMessage(const TankMessage& msg);
	sf::Vector2f RunPrediction(float gameTime);


	void SetRenderMode(const RenderMode renderMode) { m_RenderMode = renderMode; };
	void setPosition(float x, float y);
	void setGhostPosition(sf::Vector2f pos);
	void Reset();

private:
	// Tank components //
	// Body
	sf::Texture m_BodyTexture;
	float		m_BodyRotation;
	// Barrel
	sf::Texture m_BarrelTexture;
	float		m_BarrelRotation;
	sf::Sprite	m_BarrelSprite;

	// Ghost components (predicted object state)//
	sf::Sprite	m_GhostSprite; // ghost body

	// how this tank is rendered
	RenderMode	m_RenderMode = RenderMode::REAL_AND_PREDICTED;

	std::vector<TankMessage> m_Messages;
};
