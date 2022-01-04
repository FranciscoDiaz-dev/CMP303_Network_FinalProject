#include "GameState_Level.h"

#include "Framework/Input.h"
#include "NetworkSimulator.h"

GameState_Level::GameState_Level(GameStateManager* stateMgr) : GameStateBase(stateMgr)
{
	//Initialise the background texture and sprite
	floorTexture.loadFromFile("Assets/tileSand1.png");
	floorTexture.setRepeated(true);
	floor.setTexture(floorTexture);
	floor.setTextureRect(sf::IntRect(0, 0, 640, 480));

	// initialise font and text
	montserratFont.loadFromFile("Assets/Montserrat-Regular.ttf");
	debugText.setFont(montserratFont);
	debugText.setOutlineColor(sf::Color::Black);
	debugText.setOutlineThickness(1.f);

	player = gameStateManager->getSharedContext()->player;
	serversMgr = gameStateManager->getSharedContext()->serversManager;
	gameId = gameStateManager->getSharedContext()->gameId;
	clientConnection = gameStateManager->getSharedContext()->clientConnection;

	enemies.push_back(new Tank());
	enemies.push_back(new Tank());

	player->setPosition(64, 256);

	enemies.at(0)->setPosition(80, 160);
	enemies.at(0)->SetRenderMode(RenderMode::REAL_AND_PREDICTED);

	enemies.at(1)->setPosition(416, 128);
	enemies.at(1)->SetRenderMode(RenderMode::REAL_AND_PREDICTED);
}

GameState_Level::~GameState_Level()
{
	for (Tank* player: enemies)
	{
		delete player;
		player = nullptr;
	}
}

void GameState_Level::handleInput(sf::Time dt)
{
	// check if the user want to pause the game
	if (input->isKeyDown(sf::Keyboard::R))
	{
		input->setKeyUp(sf::Keyboard::R);

		// Reset players
		player->Reset();
		enemies.at(0)->Reset();
		enemies.at(0)->Reset();

		// Reset Net Simulator
		netSimulator->Reset();
		printf("\n\n--------RESET--------\n\n");
	}
}

void GameState_Level::update(sf::Time dt)
{

	// Update text
	//debugText.setString("Game Time: " + Utils::stringify(netSimulator->Time()));

	// create message
	PlayerMessage playerMsg;
	playerMsg.gameId = *gameId;
	playerMsg.playerInfo = player->getPlayerInfo();
	// send it
	if (*gameId == -1)
	{
		bool joined = clientConnection->joinAGame(&playerMsg, serversMgr->getSelectedServer().sockAddr);
		if (joined)
		{
			*gameId = playerMsg.gameId;
			player->setPlayerId(playerMsg.playerInfo.id);
		}
	}


	//If we're at the start, just advance the time by 3.5 seconds, so we have a few packets in the queue already
	if (netSimulator->Time() < 1.0f) {
		//printf("BEGIN SIMULATION\n");
		netSimulator->Update(netSimulator->getStartTime());
	}

	if (netSimulator->Time() < 19.0f) {
		PlayerInfo msg;

		//Update the network simulation
		netSimulator->Update(dt.asSeconds());
		//Get any 'network' messages that are available
		while (netSimulator->ReceiveMessage(msg)) {
			//printf("Received message: ID= %d, Pos = (%.2f, %.2f), Time =%.2f\n", msg.id, msg.x, msg.y, msg.time);
			enemies[msg.id]->AddMessage(msg);
		}

		// Get next print time
		float nextPrint = netSimulator->getNextPrint();

		// Update the player
		player->Update(dt.asSeconds());	//Update the real position of the player with the info from the latest packet

		//Update the players
		for (int i = 0; i < (int)enemies.size(); i++)
		{
			enemies.at(i)->Update(dt.asSeconds());	//Update the real position of the player with the info from the latest packet

			//Get the predicted position of the player at the current Game Time and move the ghost to that position
			enemies.at(i)->setGhostPosition(enemies.at(i)->RunPrediction(netSimulator->Time()));

			if (netSimulator->Time() > nextPrint)
			{
				//Get the predicted position of the player at a specific interval and print it to the console
				sf::Vector2f predictedPosition = enemies.at(i)->RunPrediction(nextPrint);
				//printf("\tPredicted positiion:  (%.2f, %.2f), Time =%.2f\n", predictedPosition.x, predictedPosition.y, nextPrint);
				nextPrint = nextPrint + (netSimulator->getSendRate() * 0.25f);	//Print 4 times per packet
				netSimulator->SetNextPrint(nextPrint);
			}
		}
	}
}

void GameState_Level::render()
{
	beginDraw();
		
		// Render the brackground
		window->draw(floor);

			// Render this player
			player->Render(window);

			// Render the enemies
			for (Tank* player : enemies)
			{
				player->Render(window);
			}

		// Render the text
		window->draw(debugText);

	
	endDraw();
}

void GameState_Level::goToGameOver()
{	

}