#include "GameState_Level.h"

#include "..\..\NetworkFramework\ClientConnection.h"
#include "Framework/Input.h"
#include "Tank.h"
#include "EnemiesManager.h"

GameState_Level::GameState_Level(GameStateManager* stateMgr) : GameStateBase(stateMgr)
{
	// get the pointer to the player and enemies manager 
	player = gameStateMgr->getSharedContext()->player;
	enemiesMgr = gameStateMgr->getSharedContext()->enemiesMgr;

	//Initialise the background texture and sprite
	// depending to the game id provided by the server 
	string textureFloor;
	if (*gameStateMgr->getSharedContext()->gameId % 2 == 0)	// if it is even Sand Map
		textureFloor = "tileSand1.png";
	else
		textureFloor = "tileGrass1.png"; // if it is odd then grass

	floorTexture.loadFromFile("Assets/" + textureFloor);
	floorTexture.setRepeated(true);
	floor.setTexture(floorTexture);
	floor.setTextureRect(sf::IntRect(0, 0, 640, 480));

	// initialise title text
	titleText.setString(" Game Level");

	// make a first contact with the server
	clientConnection->sendThisPlayerInfoToServer();
}

GameState_Level::~GameState_Level()
{
}

void GameState_Level::handleInput(sf::Time dt)
{
	// check if the user want to pause the game
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);

		// Exit the current Game
		if (clientConnection->exitTheGame())
		{
			// delete enemies data
			enemiesMgr->deleteEnemies();

			// reset player data
			player->Reset();

			// reset data on client connection
			clientConnection->reset();

			// go to selection again
			gameStateMgr->addToRemoveContainer(GState::LEVEL);
			gameStateMgr->switchTo(GState::SELECTION);
		}
	} 
	else if (input->isKeyDown(sf::Keyboard::W) || input->isKeyDown(sf::Keyboard::A)  ||
		input->isKeyDown(sf::Keyboard::S) || input->isKeyDown(sf::Keyboard::D))
	{
		float speed = player->GetSpeed();
		float velocity = speed * dt.asSeconds();
		sf::Vector2f currentPos = player->getPosition();
		sf::Vector2f newPos = currentPos;

		if (input->isKeyDown(sf::Keyboard::W))
		{
			input->setKeyUp(sf::Keyboard::W);
			newPos.y -= velocity;
		}
		else if (input->isKeyDown(sf::Keyboard::S))
		{
			input->setKeyUp(sf::Keyboard::S);
			newPos.y += velocity;
		}
		
		if(input->isKeyDown(sf::Keyboard::A))
		{
			input->setKeyUp(sf::Keyboard::A);
			newPos.x -= velocity;
		}
		else if (input->isKeyDown(sf::Keyboard::D))
		{
			input->setKeyUp(sf::Keyboard::D);
			newPos.x += velocity;
		}

		player->SetPosition(newPos);
		clientConnection->sendThisPlayerInfoToServer();
	}
}

void GameState_Level::update(sf::Time dt)
{
	// update player
	player->Update(dt.asSeconds());

	// check if the server has sent enemies tank infos
	// if so then get it and update them
	clientConnection->getEnemiesInfos(dt.asSeconds());

	// update enemies
	enemiesMgr->update(dt.asSeconds());
}

void GameState_Level::render()
{
	beginDraw();
		
		// Render the brackground
		window->draw(floor);

		// Render this player
		player->Render(window);

		// Render the enemies
		enemiesMgr->render(window);

		// Render the texts
		window->draw(titleText);
		window->draw(infoText);

	
	endDraw();
}