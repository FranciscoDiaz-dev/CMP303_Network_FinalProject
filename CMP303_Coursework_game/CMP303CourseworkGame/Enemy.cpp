#include "Enemy.h"

Enemy::Enemy(float* timeSinceLastTankInfoReceived)
	: m_TimeSinceLastTankInfoReceived(timeSinceLastTankInfoReceived), m_NumPastTankInfosToPredict(2)
{
}

Enemy::~Enemy()
{
}


void Enemy::HandleInput(float dt)
{
}

void Enemy::Update(float dt)
{
	if (m_PredictionType != nullptr && int(*m_PredictionType) > 0
		&& int(m_PastTankInfos.size()) == m_NumPastTankInfosToPredict)
	{
		setGhostPosition(RunPrediction());
	}
}

void Enemy::Render(sf::RenderWindow* window)
{
	// Render Ghost
	if (int(*m_PredictionType) > 0 && int(m_PastTankInfos.size()) == m_NumPastTankInfosToPredict)
	{
		window->draw(m_GhostSprite);
	}

	// Render real tank
	Tank::Render(window);

	// set to false so during the next tankInfo received from the server will be false if no new info was received
	m_TankInfoReceived = false;
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
	// add to the collection the current tankInfo
	// because this enemy has received a new one
	m_PastTankInfos.push_back(m_TankInfo);

	// update the tank info variable with the latest received
	Tank::SetTankInfo(latestTanksInfo);

	// remove the oldest tank info if the amount of message in the collection
	// is bigger than needed to calculate predictions
	if (int(m_PastTankInfos.size()) > m_NumPastTankInfosToPredict)
	{
		m_PastTankInfos.erase(m_PastTankInfos.begin());
	}

	// set this tanks has received the latest info
	m_TankInfoReceived = true;

	// check if it is idle
	for (int i = 0; i < int(m_PastTankInfos.size()); i++)
	{
		if (m_PastTankInfos.at(i).time != m_TankInfo.time)
		{
			m_IsIdle = false;
			return;
		}
	}

	// if the function reachs here then mean the player is idle
	m_IsIdle = true;
}

sf::Vector2f Enemy::RunPrediction()
{
	float predictedX = -1.0f;
	float predictedY = -1.0f;

	const int msize = m_PastTankInfos.size();
	if (msize < m_NumPastTankInfosToPredict)
	{
		return sf::Vector2f(predictedX, predictedX);
	}
	const TankInfo& msg0 = m_TankInfo; // latest position
	const TankInfo& msg1 = m_PastTankInfos[msize - 1]; // penultimate position
	const TankInfo& msg2 = m_PastTankInfos[msize - 2]; // antepenultimate position

	// This function has:
	// - the history of position messages received, in "m_PastTankInfos"
	//   (msg0 is the most recent, msg1 the 2nd most recent, msg2 the 3rd most recent)
	// - the current time, in "time" hereditated from "Tank.h"
	// This functions does:
	// - the predicted position at the current time, in "predictedX" and "predictedY"

	if (*m_PredictionType == PredictionType::LINEAR)
	{

		// Linear Prediction (it uses the last two known positions to extrapolate the next position)
		// Next position = previous real position + displacement
		// Displacemenent = speed * time(since last message)
		// Speed = (distance between the last two position)/ (time between the last two positions)
		sf::Vector2f speedL = (sf::Vector2f(msg0.x, msg0.y) - sf::Vector2f(msg1.x, msg1.y)) / (msg0.time - msg1.time);
		sf::Vector2f displacementL = speedL * (*m_TimeSinceLastTankInfoReceived);
		sf::Vector2f nextPosL = getPosition() + displacementL;
		predictedX = nextPosL.x;
		predictedY = nextPosL.y;
	}
	else if (*m_PredictionType == PredictionType::QUADRATIC)
	{

		// Quadratic Prediction ( it uses the three last known positions to extrapolate the next position)
		// S = ut + 0.5*a*t^2
		// Next position = previous real position + displacement
		// Displacement = speed(at last message) * time(since last message) + 0.5 * acceleration * time^2
		// Speed = distance between the last two positions/ time between last two position.
		// Acceleration = difference in speed at the last two positions / time between those positions.
		sf::Vector2f speed0Q = (sf::Vector2f(msg0.x, msg0.y) - sf::Vector2f(msg1.x, msg1.y)) / (msg0.time - msg1.time);
		sf::Vector2f speed1Q = (sf::Vector2f(msg1.x, msg1.y) - sf::Vector2f(msg2.x, msg2.y)) / (msg1.time - msg2.time);
		sf::Vector2f accelerationQ = (speed1Q - speed0Q) / (msg0.time - msg1.time);
		sf::Vector2f displacementQ = (speed0Q * (*m_TimeSinceLastTankInfoReceived)) + (0.5f * accelerationQ * powf((*m_TimeSinceLastTankInfoReceived), 2.0f));
		sf::Vector2f nextPosQ = getPosition() + displacementQ;
		predictedX = nextPosQ.x;
		predictedY = nextPosQ.y;
	}

	return sf::Vector2f(predictedX, predictedY);
}

void Enemy::Reset()
{
	// Reset basic stats of this tank
	Tank::Reset();

	// Remove all the info
	m_PastTankInfos.clear();
}
