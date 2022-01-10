#include "EnemiesManager.h"

EnemiesManager::EnemiesManager()
{
}

EnemiesManager::~EnemiesManager()
{
	deleteEnemies();
}

void EnemiesManager::setEnemiesInfos(std::vector<TankInfo>& enemiesInfo)
{
	Enemy* enemy;

	// Loop for the latest enemy's infomation obtained
	for (TankInfo enemyInfo : enemiesInfo)
	{
		// get a pointer of our current enemy data
		enemy = findEnemyById(enemyInfo.id);

		// If the enemy exits on this client side and it contains an older information than 
		// the one received then update it
		if (enemy != nullptr && enemy->getTankInfo().time < enemyInfo.time) 
		{
			// save the latest info received
			enemy->setTankInfo(enemyInfo);
		}
		// If the enemy has not been created yet on this client side
		// then create it
		else if(enemy == nullptr)
		{
			Enemy* newEnemy = new Enemy();
			newEnemy->setTankInfo(enemyInfo);
			enemies.insert(std::pair<int, Enemy*>(enemyInfo.id, newEnemy));
		}
	}
}

void EnemiesManager::update(float dt)
{
	for (auto enemy : enemies)
	{
		enemy.second->Update(dt);
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

void EnemiesManager::deleteEnemies()
{
	for (auto enemy : enemies)
	{
		delete enemy.second;
		enemy.second = nullptr;
	}

	enemies.clear();
}

int EnemiesManager::getNumActiveEnemies()
{
	return int(enemies.size());
}

Enemy* EnemiesManager::findEnemyById(int id)
{
	auto it = enemies.find(id);
	if (it != enemies.end())
		return it->second;
	else
		return nullptr;
}