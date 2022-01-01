#include "Tank.h"
#include "Utils.h"


Tank::Tank() : sf::Sprite()
{
	m_PlayerName = "Player X";
	SetColour("Red");
}


Tank::~Tank()
{
}


void Tank::Update(float dt)
{
	if (m_Messages.size() < 1)
		return;
	TankMessage latestMessage = m_Messages.back();
	setPosition(latestMessage.x, latestMessage.y);
}

void Tank::setPosition(float x, float y) {
	sf::Sprite::setPosition(x, y);
	m_BarrelSprite.setPosition(getPosition());
}


void Tank::setGhostPosition(sf::Vector2f pos) {
	m_GhostSprite.setPosition(pos);
}

void Tank::SetColour(std::string colour)
{
	m_Colour = colour;

	// Change texture
	m_BodyTexture.loadFromFile("Assets/" + m_Colour + "Tank.png");
	m_BarrelTexture.loadFromFile("Assets/" + m_Colour + "Barrel.png");
	setTexture(m_BodyTexture);

	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);

	m_GhostSprite.setTexture(m_BodyTexture);
	m_GhostSprite.setColor(sf::Color(255, 255, 255, 128));
	m_GhostSprite.setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	setGhostPosition(getPosition());

	m_BarrelSprite.setTexture(m_BarrelTexture);
	m_BarrelSprite.setOrigin(6, 2);
	m_BarrelSprite.setPosition(getPosition());
}

const void Tank::Render(sf::RenderWindow* window) {
	if ((int)m_RenderMode > 0)
	{
		window->draw(m_GhostSprite);
	}
	if ((int)m_RenderMode != 1) {
		window->draw(*this);
		window->draw(m_BarrelSprite);
	}
}

void Tank::AddMessage(const TankMessage& msg) {
	m_Messages.push_back(msg);
}


sf::Vector2f Tank::RunPrediction(float gameTime) {
	float predictedX = -1.0f;
	float predictedY = -1.0f;

	const int msize = m_Messages.size();
	if (msize < 3) {
		return sf::Vector2f(predictedX, predictedX);
	}
	const TankMessage& msg0 = m_Messages[msize - 1];
	const TankMessage& msg1 = m_Messages[msize - 2];
	const TankMessage& msg2 = m_Messages[msize - 3];

	// FIXME: Implement prediction here!
	// You have:
	// - the history of position messages received, in "m_Messages"
	//   (msg0 is the most recent, msg1 the 2nd most recent, msg2 the 3rd most recent)
	// - the current time, in "gameTime"
	//
	// You need to update:
	// - the predicted position at the current time, in "predictedX" and "predictedY"

	// Using the lastest message received (not prediction)
	//predictedX = msg0.x;
	//predictedY = msg0.y;

	// Linear Prediction (it uses the last two known positions to extrapolate the next position)
	// Next position = previous real position + displacement
	// Displacemenent = speed * time(since last message)
	// Speed = (distance between the last two position)/ (time between the last two positions)
	sf::Vector2f speedL = (sf::Vector2f(msg0.x, msg0.y) - sf::Vector2f(msg1.x, msg1.y)) / (msg0.time - msg1.time);
	sf::Vector2f displacementL = speedL * (gameTime - msg0.time);
	sf::Vector2f nextPosL = getPosition() + displacementL;
	predictedX = nextPosL.x;
	predictedY = nextPosL.y;

	// Quadratic Prediction ( it uses the three last known positions to extrapolate the next position)
	// S = ut + 0.5*a*t^2
	// Next position = previous real position + displacement
	// Displacement = speed(at last message) * time(since last message) + 0.5 * acceleration * time^2
	// Speed = distance between the last two positions/ time between last two position.
	// Acceleration = difference in speed at the last two positions / time between those positions.
	sf::Vector2f speed0Q = (sf::Vector2f(msg0.x, msg0.y) - sf::Vector2f(msg1.x, msg1.y)) / (msg0.time - msg1.time);
	sf::Vector2f speed1Q = (sf::Vector2f(msg1.x, msg1.y) - sf::Vector2f(msg2.x, msg2.y)) / (msg1.time - msg2.time);
	sf::Vector2f accelerationQ = (speed1Q - speed0Q) / (msg0.time - msg1.time);
	sf::Vector2f displacementQ = (speed0Q * (gameTime - msg0.time)) + (0.5f * accelerationQ * powf((gameTime - msg0.time), 2.0f));
	sf::Vector2f nextPosQ = getPosition() + displacementQ;
	predictedX = nextPosQ.x;
	predictedY = nextPosQ.y;

	return sf::Vector2f(predictedX, predictedY);
}

void Tank::Reset() {
	m_Messages.clear();
}