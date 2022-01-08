// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the Game states manager.
// @author Paul Robertson
// @modify by Francisco Diaz (@FMGameDev)
// - added windowProcess function to group the events (having as model the examples in the labs by Paul Robertson)
// - added a shared Context which contains all the data necessary in the game states for the correct operation of the game.
// as we have declared here the objects in the shared context these won't be loss during all the time that the user is playing

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Framework/Input.h"
#include "GameStateManager.h"
#include "NetworkSimulator.h"
#include "../../NetworkFramework/ServersListManager.h"
#include "../../NetworkFramework/ClientConnection.h"
#include "EnemiesManager.h"
#include "Tank.h"
#include <Windows.h> // for get the local time


#include "SharedContext.h"
#include "GUI.h"


// Control of window events
void windowProcess(sf::RenderWindow* window, Input* in, GUI* gui, const unsigned int& MIN_WIDTH, const unsigned int& MIN_HEIGHT)
{
	// Handle window events.
	sf::Event event;
	while (window->pollEvent(event))
	{
		// process event for the gui if it exists
		if(gui != nullptr)
			gui->processEvent(event);

		// process windows event
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			// control minimun size of the window
			if ((float)event.size.width >= MIN_WIDTH && (float)event.size.height >= MIN_HEIGHT) // if the new size is bigger than the minimum size
			{
				window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
			}
			else // Deny if the user try to decrease the window less than the min_width/height 
			{
				window->setSize(sf::Vector2u((unsigned int)MIN_WIDTH, (unsigned int)MIN_HEIGHT));
				window->setView(sf::View(sf::FloatRect(0.0f, 0.0f, (float)MIN_WIDTH, (float)MIN_HEIGHT)));
			}
			break;
		case sf::Event::KeyPressed:
			// update input class
			in->setKeyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			//update input class
			in->setKeyUp(event.key.code);
			break;
		case sf::Event::MouseMoved:
			//update input class
			in->setMousePosition(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
				in->setMouseLDown(true);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setMouseRDown(true);
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
				in->setMouseLDown(false);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setMouseRDown(false);
			}
			break;
		default:
			// don't handle other events
			break;
		}
	}
}

// main game menu
int main()
{
	// Create Objects to shared in the game states
	const sf::String kGameName = "CMP303 - Coursework by Francisco Diaz (1902654) - GAME";
	const unsigned int kMinWindowWith = 640;
	const unsigned int kMinWindowHeight = 480;
	sf::RenderWindow window(sf::VideoMode(kMinWindowWith, kMinWindowHeight), kGameName);
	window.setFramerateLimit(60);	//Request 60 frames per second

	Input input; // imput component used in all the game
	GameState gameState; // game state component which contains the current game state
	Tank player;
	EnemiesManager enemiesMgr;
	int gameId = -1;

	//Create a network simulator with that "sends" a message every 0.5 seconds and has a latency of 0.3 seconds
	float sendRate = 0.5f;
	float latency = 0.3f;
	NetworkSimulator netSimulator(sendRate, latency);
	netSimulator.m_MyID = 0;	//On the network, we are Tank 0

	ClientConnection clientConnection(&player, &gameId, &gameState);
	ServersListManager serversListMgr;

	// Create SharedContext which it contains all the components we will need in the game states
	SharedContext sharedContext;
	sharedContext.kGameName = &kGameName;
	sharedContext.kMinWindowWith = &kMinWindowWith;
	sharedContext.kMinWindowHeight = &kMinWindowHeight;
	sharedContext.window = &window;
	sharedContext.input = &input;
	sharedContext.netSimulator = &netSimulator;
	sharedContext.gameState = &gameState;
	sharedContext.serversListMgr = &serversListMgr;
	sharedContext.player = &player;
	sharedContext.enemiesMgr = &enemiesMgr;
	sharedContext.gameId = &gameId;
	sharedContext.clientConnection = &clientConnection;

	// Initilise GameStateManager 
	GameStateManager gameStateMgr(&sharedContext);

	// Set initial game state
	gameStateMgr.switchTo(GState::SELECTION);

	// Initialise objects for delta time
	sf::Clock gameClock;
	sf::Time deltaTime;

	// Game Loop
	while (sharedContext.window->isOpen())
	{
		//Process window events
		windowProcess(sharedContext.window, sharedContext.input, sharedContext.gui, kMinWindowWith, kMinWindowHeight);

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock->
		deltaTime = gameClock.restart();
		
		// Call standard game loop functions (input, update and render)
		gameStateMgr.handleInput(deltaTime);	
		gameStateMgr.update(deltaTime);
		gameStateMgr.render();

		// process all the resquest asked
		// this method will remove the game states objects requested to be removed
		gameStateMgr.processRequests();
	}

	return 0;
}

