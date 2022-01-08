#include "EnemiesManager.h"

EnemiesManager::EnemiesManager()
{
}

EnemiesManager::~EnemiesManager()
{
	for (auto enemy : enemies)
	{
		delete enemy.second;
		enemy.second = nullptr;
	}

	enemies.clear();
}

void EnemiesManager::update(float dt, std::vector<TankInfo>& enemiesInfo)
{
	Enemy* enemy;

	// Loop for the array
	for (TankInfo enemyInfo : enemiesInfo)
	{
		enemy = findEnemyById(enemyInfo.id);

		// If the enemy exits on this client side and it contains an older information than the received
		// then update it
		if (enemy != nullptr && enemy->getTankInfo().time < enemyInfo.time) 
		{
			// save the latest info received
			enemy->setTankInfo(enemyInfo);
			// update the enemy
			enemy->Update(dt);
		}
		// if the enemy has not been created yet on this client side
		// then create it
		else if(enemy == nullptr)
		{
			Enemy* newEnemy = new Enemy();
			newEnemy->setTankInfo(enemyInfo);
			enemies.insert(std::pair<int, Enemy*>(enemyInfo.id, newEnemy));
		}
	}
}

void EnemiesManager::render(sf::RenderWindow* window)
{
	for (auto enemy : enemies)
	{
		if(enemy.second->GetId() != -1)
			enemy.second->Render(window);
	}
}

void EnemiesManager::resetEnemies()
{
	for (auto enemy : enemies)
	{
		enemy.second->Reset();
	}
}

Enemy* EnemiesManager::findEnemyById(int id)
{
	auto it = enemies.find(id);
	if (it != enemies.end())
		return it->second;
	else
		return nullptr;
}