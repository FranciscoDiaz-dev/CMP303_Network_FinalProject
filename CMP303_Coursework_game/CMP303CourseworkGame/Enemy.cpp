#include "Enemy.h"

Enemy::Enemy()
{
	// by default render ghost(predicted position) and real one
	m_RenderMode = RenderMode::REAL_AND_PREDICTED;
}

Enemy::~Enemy()
{
}


void Enemy::HandleInput(float dt)
{
}

void Enemy::Update(float dt)
{
	if (int(m_RenderMode) > 0 && int(m_Messages.size()) > 4)
	{
		setGhostPosition(RunPrediction(dt));
	}
}

void Enemy::Render(sf::RenderWindow* window)
{
	// Render Ghost
	if ((int)m_RenderMode > 0 && int(m_Messages.size()) > 4)
	{
		window->draw(m_GhostSprite);
	}

	// Render real tank
	if ((int)m_RenderMode != 1)
	{
		Tank::Render(window);
	}
}


void Enemy::setGhostPosition(sf::Vector2f pos)
{
	m_GhostSprite.setPosition(pos);
}

void Enemy::SetTexture(std::string colour)
{
	// Upate Body texture and save colour
	Tank::SetTexture(colour);

	// Update Ghost Texture
	m_GhostSprite.setTexture(m_BodyTexture);
	m_GhostSprite.setColor(sf::Color(255, 255, 255, 128));
	m_GhostSprite.setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	setGhostPosition(getPosition());
}

void Enemy::SetTankInfo(const TankInfo latestTanksInfo)
{
	// update the tank info
	Tank::SetTankInfo(latestTanksInfo);

	// add it to the collection
    m_Messages.push_back(latestTanksInfo);

	// remove the oldest message if the amount of message in the collection
	// is bigger than needed to calculate predictions
	if (int(m_Messages.size()) > 4)
	{
		m_Messages.erase(m_Messages.begin());
	}
}

sf::Vector2f Enemy::RunPrediction(float gameTime)
{
	float predictedX = -1.0f;
	float predictedY = -1.0f;

	const int msize = m_Messages.size();
	if (msize < 3) {
		return sf::Vector2f(predictedX, predictedX);
	}
	const TankInfo& msg0 = m_Messages[msize - 1]; // latest position
	const TankInfo& msg1 = m_Messages[msize - 2]; // penultimate position
	const TankInfo& msg2 = m_Messages[msize - 3]; // antepenultimate position

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

void Enemy::Reset()
{
	// Reset basic stats of this tank
	Tank::Reset();

	// Remove all the info
	m_Messages.clear();
}
