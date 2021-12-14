#include "GameState_Level.h"

#include "Utils.h"
#include "Framework/Input.h"
#include "NetworkSimulator.h"

GameState_Level::GameState_Level(GameStateManager* stateMgr) : GameStateBase(stateMgr)
{
	tanks.push_back(new Tank("green"));
	tanks.push_back(new Tank("blue"));

	tanks.at(0)->setPosition(64, 256);

	tanks.at(1)->setPosition(416, 128);
	tanks.at(1)->SetRenderMode(Tank::RenderMode::REAL_AND_PREDICTED);

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
}

GameState_Level::~GameState_Level()
{
	for (Tank* tank: tanks)
	{
		delete tank;
		tank = nullptr;
	}
}

void GameState_Level::handleInput(float dt)
{

	// check if the user want to pause the game
	if (input->isKeyDown(sf::Keyboard::R))
	{
		input->setKeyUp(sf::Keyboard::R);

		// Reset tanks
		tanks.at(0)->Reset();
		tanks.at(0)->Reset();

		// Reset Net Simulator
		netSimulator->Reset();
		printf("\n\n--------RESET--------\n\n");
	}
	
}

void GameState_Level::update(float dt)
{
	// Update text
	debugText.setString("Game Time: " + Utils::stringify(netSimulator->Time()));

	//If we're at the start, just advance the time by 3.5 seconds, so we have a few packets in the queue already
	if (netSimulator->Time() < 1.0f) {
		printf("BEGIN SIMULATION\n");
		netSimulator->Update(netSimulator->getStartTime());
	}

	if (netSimulator->Time() < 19.0f) {
		TankMessage msg;

		//Update the network simulation
		netSimulator->Update(dt);
		//Get any 'network' messages that are available
		while (netSimulator->ReceiveMessage(msg)) {
			printf("Received message: ID= %d, Pos = (%.2f, %.2f), Time =%.2f\n", msg.id, msg.x, msg.y, msg.time);
			tanks[msg.id]->AddMessage(msg);
		}

		// Get next print time
		float nextPrint = netSimulator->getNextPrint();

		//Update the tanks
		for (int i = 0; i < (int)tanks.size(); i++)
		{
			tanks.at(i)->Update(dt);	//Update the real position of the tank with the info from the latest packet

			if (i != netSimulator->m_MyID)
			{
				//Get the predicted position of the tank at the current Game Time and move the ghost to that position
				tanks.at(i)->setGhostPosition(tanks.at(i)->RunPrediction(netSimulator->Time()));

				if (netSimulator->Time() > nextPrint)
				{
					//Get the predicted position of the tank at a specific interval and print it to the console
					sf::Vector2f predictedPosition = tanks.at(i)->RunPrediction(nextPrint);
					printf("\tPredicted positiion:  (%.2f, %.2f), Time =%.2f\n", predictedPosition.x, predictedPosition.y, nextPrint);
					nextPrint = nextPrint + (netSimulator->getSendRate() * 0.25f);	//Print 4 times per packet
					netSimulator->SetNextPrint(nextPrint);
				}
			}
		}
	}
}

void GameState_Level::render()
{
	beginDraw();
		
		// Render the brackground
		window->draw(floor);

		// Render the tanks
		for (Tank* tank : tanks)
		{
			tank->Render(window);
		}

		// Render the text
		window->draw(debugText);
	
	endDraw();
}

void GameState_Level::goToGameOver()
{	

}