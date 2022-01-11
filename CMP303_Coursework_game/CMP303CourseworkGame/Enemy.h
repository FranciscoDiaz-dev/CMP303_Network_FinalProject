#ifndef _ENEMY_H
#define _ENEMY_H
#pragma once

// Enemy
// Add the prediction functionality to the tank object
// Enemy extend from Tank,
// @author Francisco Diaz (@FMGameDev)

#include "Tank.h"

// How to calculate prediction
enum class PredictionType
{
	NONE = 0, // no calculation
	LINEAR,
	QUADRATIC
};

class Enemy : public Tank
{
public:
	// constructor
	Enemy(float* timeSinceLastTankInfoReceived);
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

	// Set the texture(and colour) of this tank (barrel, body and the ghost)
	void SetTexture(std::string colour) override;

	// Add a message to the enemy network message queue
	void SetTankInfo(const TankInfo latestTanksInfo) override;

	bool IsIdle()const { return m_IsIdle; };

	// This method calculates and stores the gosh (predicted) position, using the three latest tanks info received
	// and the time has been since the last info was received.
	sf::Vector2f RunPrediction();

	// return the time when this enemy sent their "last" tankInfo to the server (the latest info received)
	float getLastInfoTankTime() { return m_PastTankInfos.back().time; };

	// return if this tank received the tank info in the last update
	bool wasTankInfoReceived() const { return m_TankInfoReceived; };

	// set the prediction type for this enemy
	void setPredictionType(PredictionType* predictionType) { m_PredictionType = predictionType; };

	// Reset all the tank info
	void Reset() override;

private:
	// Component where we will be reading the player stats for prediction
	std::vector<TankInfo> m_PastTankInfos;
	// the number of tank info neccessary to use prediction
	int m_NumPastTankInfosToPredict;
	// pointing to the variable on EnemyManager
	float* m_TimeSinceLastTankInfoReceived; 

	// if all the last three tank infos received for this player is the same
	// it is used for detecting if the player is idle, so no more tank info is received until
	// a most updated time is received
	bool m_IsIdle; 

	// Ghost components (predicted object state)//
	// it uses the same texture than this object
	sf::Sprite	m_GhostSprite; // ghost body

	// How this enemy prediction is calculated (in case it is)
	PredictionType* m_PredictionType;

	// if this tank received the tank info in the last update
	bool m_TankInfoReceived;
};

#endif // _ENEMY_H

