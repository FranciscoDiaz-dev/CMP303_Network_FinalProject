#include "Tank.h"


Tank::Tank() : sf::Sprite()
{
	//Reset();
}


Tank::~Tank()
{
}


void Tank::HandleInput(float dt)
{
}

void Tank::Update(float dt)
{
}

void Tank::Render(sf::RenderWindow* window)
{
	window->draw(*this);
	window->draw(m_BarrelSprite);
}


void Tank::setTankInfo(TankInfo newTankInfo)
{
	// Check if this tank had another texture/colour
	// if so then update it
	if (m_TankInfo.colour != newTankInfo.colour)
	{
		SetTexture(newTankInfo.colour);
	}

	// Set Position
	SetPosition(sf::Vector2f(newTankInfo.x, newTankInfo.y));

	// update the full tank info
	m_TankInfo = newTankInfo;
}

void Tank::SetTexture(std::string colour)
{
	// save player colour
	m_TankInfo.colour = colour;

	// Change Body texture
	m_BodyTexture.loadFromFile("Assets/" + m_TankInfo.colour + "Tank.png");
	m_BarrelTexture.loadFromFile("Assets/" + m_TankInfo.colour + "Barrel.png");
	sf::Sprite::setTexture(m_BodyTexture);
	sf::Sprite::setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);

	// Change Barrel Texture
	m_BarrelSprite.setTexture(m_BarrelTexture);
	m_BarrelSprite.setOrigin(6, 2);
	m_BarrelSprite.setPosition(sf::Sprite::getPosition());
}

void Tank::Reset()
{
	// Set a new player info
	setTankInfo(TankInfo());
}

void Tank::SetPosition(sf::Vector2f pos)
{
	// set position of the body sprite
	sf::Sprite::setPosition(pos.x, pos.y);

	// set position of the barrel sprite
	m_BarrelSprite.setPosition(sf::Sprite::getPosition());

	// save position in the player info struc
	m_TankInfo.x = pos.x;
	m_TankInfo.y = pos.y;
	m_TankInfo.time = 1.0f; // TODO: MOVE TO ANOTHER PLACE
}
