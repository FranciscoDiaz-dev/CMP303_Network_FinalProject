#include "GameState_Level.h"

#include "Framework/Input.h"
#include "NetworkSimulator.h"

GameState_Level::GameState_Level(GameStateManager* stateMgr) : GameStateBase(stateMgr)
{
	player = gameStateMgr->getSharedContext()->player;
	enemiesMgr = gameStateMgr->getSharedContext()->enemiesMgr;
	gameId = gameStateMgr->getSharedContext()->gameId;
	clientConnection = gameStateMgr->getSharedContext()->clientConnection;

	//Initialise the background texture and sprite
	string textureFloor;
	// Sand
	if (*gameId == 0)	// Sand Map
		textureFloor = "tileSand1.png";
	else				// Texture Map
		textureFloor = "tileGrass1.png";

	floorTexture.loadFromFile("Assets/" + textureFloor);
	floorTexture.setRepeated(true);
	floor.setTexture(floorTexture);
	floor.setTextureRect(sf::IntRect(0, 0, 640, 480));

	// initialise font and text
	montserratFont.loadFromFile("Assets/Montserrat-Regular.ttf");
	debugText.setFont(montserratFont);
	debugText.setOutlineColor(sf::Color::Black);
	debugText.setOutlineThickness(1.f);



	// Initialise postion of the player
	player->SetPosition(sf::Vector2f(64, 256));
}

GameState_Level::~GameState_Level()
{
}

void GameState_Level::handleInput(sf::Time dt)
{
	// check if the user want to pause the game
	if (input->isKeyDown(sf::Keyboard::R))
	{
		input->setKeyUp(sf::Keyboard::R);

		// Reset players
		player->Reset();
		enemiesMgr->resetEnemies();
	}
}

void GameState_Level::update(sf::Time dt)
{

	// create message
	PlayerMessage playerMsg;
	playerMsg.gameId = *gameId;
	playerMsg.tankInfo = player->getTankInfo();

	// Connection to server

	// Update player
	player->Update(dt.asSeconds());

	// Update enemies
	//enemiesMgr->update(dt.asSeconds(), clientConnection->getPlayersInfo());
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

		// Render the text
		window->draw(debugText);

	
	endDraw();
}

void GameState_Level::goToGameOver()
{	

}