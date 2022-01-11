#include "EnemiesManager.h"

EnemiesManager::EnemiesManager()
{
	timeSinceLastTankInfoReceived = 0.0f;
}

EnemiesManager::~EnemiesManager()
{
	deleteEnemies();
}

void EnemiesManager::updateEnemiesInfos(std::vector<TankInfo> enemiesInfo)
{
	Enemy* enemy;

	// Loop for the latest enemy's infomation obtained
	for (TankInfo enemyInfo : enemiesInfo)
	{
		// get a pointer of our current enemy data
		enemy = findEnemyById(enemyInfo.id);

		// If the enemy exits on this client side and it contains an older information than 
		// the one received then update it
		if (enemy != nullptr && (enemy->GetTankInfo().time < enemyInfo.time || !enemy->IsIdle())) 
		{
			// save the latest info received
			enemy->SetTankInfo(enemyInfo);
		}
		// If the enemy has not been created yet on this client side
		// then create it
		else if(enemy == nullptr)
		{
			Enemy* newEnemy = new Enemy(&timeSinceLastTankInfoReceived);
			newEnemy->SetTankInfo(enemyInfo);
			newEnemy->setPredictionType(&predictionType);
			enemies.insert(std::pair<int, Enemy*>(enemyInfo.id, newEnemy));
		}
	}

	// If we have more enemies than the server has, this means that at least one
	// enemy left the game because the server deleted it on its side
	// thus we need to delete it on this client side
	if (enemiesInfo.size() < enemies.size())
	{
		// contain all the enemies id which must be deleted
		std::vector<int> enemiesToErase;
		// look for the enemies key/ids to delete on the collection
		for (auto enemy : enemies)
		{
			if (!enemy.second->wasTankInfoReceived())
				enemiesToErase.push_back(enemy.first);
		}
		// delete it
		for (int key : enemiesToErase)
		{
			enemies.erase(key);
		}
	}

	// reset timer
	timeSinceLastTankInfoReceived = 0.0f;
}

void EnemiesManager::update(float dt)
{
	// update all the enemies
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