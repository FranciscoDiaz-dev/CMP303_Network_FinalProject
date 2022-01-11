#include "Tank.h"


Tank::Tank() : sf::Sprite()
{
	// Initialise font and text
	m_MontserratFont.loadFromFile("Assets/Montserrat-Regular.ttf");

	m_TankNameText.setFont(m_MontserratFont);
	m_TankNameText.setOutlineColor(sf::Color::Black);
	m_TankNameText.setOutlineThickness(1.f);
	m_TankNameText.setCharacterSize(10);
	m_TankNameText.setPosition(sf::Vector2f(250.0f, 20.0f));

	m_TankScoreText.setFont(m_MontserratFont);
	m_TankScoreText.setOutlineColor(sf::Color::Black);
	m_TankScoreText.setOutlineThickness(1.f);
	m_TankScoreText.setCharacterSize(10);
	m_TankScoreText.setPosition(sf::Vector2f(250.0f, 20.0f));

	m_TankNameText.setString(m_TankInfo.name);
}


Tank::~Tank()
{
}


void Tank::HandleInput(float dt)
{
}

void Tank::Update(float dt)
{
	// move the tank if it is a bot
	m_TankInfo.time += dt;
}

void Tank::Render(sf::RenderWindow* window)
{
	window->draw(*this);
	window->draw(m_BarrelSprite);
	window->draw(m_TankNameText);
	window->draw(m_TankScoreText);
}


void Tank::SetTankInfo(TankInfo newTankInfo)
{
	// Check if this tank had another texture/colour
	// if so then update it
	if (m_TankInfo.colour != newTankInfo.colour)
	{
		SetTexture(newTankInfo.colour);
	}

	// Set Position of the tank
	SetPosition(sf::Vector2f(newTankInfo.x, newTankInfo.y));

	// Set Texts
	if (m_TankInfo.name == newTankInfo.name)
	{
		m_TankNameText.setString(newTankInfo.name);
	}

	// update the full tank info variable/container
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
	SetTankInfo(TankInfo());
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

	// Set position of the texts
	m_TankNameText.setPosition(sf::Vector2f(pos.x + 22, pos.y - 30)); // up and right
	m_TankScoreText.setPosition(sf::Vector2f(pos.x + 22, pos.y - 18)); // up and right
}
