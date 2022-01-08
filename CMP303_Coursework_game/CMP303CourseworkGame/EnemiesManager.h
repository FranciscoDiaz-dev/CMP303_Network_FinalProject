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

	void update(float dt, std::vector<TankInfo>& enemiesInfo);
	void render(sf::RenderWindow* window);

	// reset all the enemies
	void resetEnemies();

private:
	// colelction of enemies
	// ordered by its id
	std::map<int, Enemy*> enemies;

	Enemy* findEnemyById(int id);
};

#endif //_ENEMIES_MANAGER_H

