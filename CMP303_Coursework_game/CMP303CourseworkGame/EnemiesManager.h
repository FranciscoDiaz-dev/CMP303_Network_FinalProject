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
	void setEnemiesInfos(std::vector<TankInfo>& enemiesInfo);

	void update(float dt);

	// render the enemies
	void render(sf::RenderWindow* window);

	// delete all the enemies from the collection
	void deleteEnemies();

	// return the number of enemies which are activated
	int getNumActiveEnemies();

private:
	// colelction of enemies
	// ordered by its id
	std::map<int, Enemy*> enemies;

	// find an enemy by its id
	// return nullptr if it is not found
	Enemy* findEnemyById(int id);

};

#endif //_ENEMIES_MANAGER_H

