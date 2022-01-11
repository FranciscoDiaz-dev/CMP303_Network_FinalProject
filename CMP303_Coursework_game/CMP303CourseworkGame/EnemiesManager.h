#ifndef _ENEMIES_MANAGER_H
#define _TENEMIES_MANAGER_H
#pragma once

#include <SFML\Graphics.hpp>
#include <map>
#include "Enemy.h"

class EnemiesManager
{
public:
	// constructor
	EnemiesManager();

	// destructor
	~EnemiesManager();

	// update all the enemy info
	// if the collection is empty (no new info received)
	// then add the delta time to the variable which trackle this 
	// if infos were received then reset the timer
	void updateEnemiesInfos(std::vector<TankInfo> enemiesInfo);

	// update all the enemies
	void update(float dt);

	// render the enemies
	void render(sf::RenderWindow* window);

	// delete all the enemies from the collection
	void deleteEnemies();

	// return the number of enemies which are activated
	int getNumActiveEnemies();

	// add to the timer
	void updatesNotReceived(float dt) { timeSinceLastTankInfoReceived += dt;};

	int getPredictionType() { return int(predictionType); };
	void setPredictionType(int predictionTypeInt) { predictionType = PredictionType(predictionTypeInt); };

private:
	// colelction of enemies
	// ordered by its id
	std::map<int, Enemy*> enemies;

	// find an enemy by its id
	// return nullptr if it is not found
	Enemy* findEnemyById(int id);

	// prediction type of the enemies
	PredictionType predictionType;
	float timeSinceLastTankInfoReceived;
};

#endif //_ENEMIES_MANAGER_H

