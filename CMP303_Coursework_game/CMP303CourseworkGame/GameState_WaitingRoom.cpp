#include "GameState_WaitingRoom.h"

#include "Framework/Input.h"
#include "NetworkSimulator.h"

GameState_WaitingRoom::GameState_WaitingRoom(GameStateManager* stateMgr) : GameStateBase(stateMgr)
{
	// initialise font and text
	montserratFont.loadFromFile("Assets/Montserrat-Regular.ttf");

	titleText.setFont(montserratFont);
	titleText.setOutlineColor(sf::Color::Black);
	titleText.setOutlineThickness(1.f);
	titleText.setString(" Waiting Room");

	infoText.setFont(montserratFont);
	infoText.setOutlineColor(sf::Color::Black);
	infoText.setOutlineThickness(1.f);
	infoText.setCharacterSize(20);	
	infoText.setPosition(sf::Vector2f(titleText.getPosition().x + 410.0f, titleText.getPosition().y + 10.0f));

	// get the objects to use on this class from the shared context
	player = gameStateMgr->getSharedContext()->player;
	clientConnection = gameStateMgr->getSharedContext()->clientConnection;
	gameId = gameStateMgr->getSharedContext()->gameId;
	gameState = gameStateMgr->getSharedContext()->gameState;
	enemiesMgr = gameStateMgr->getSharedContext()->enemiesMgr;
}

GameState_WaitingRoom::~GameState_WaitingRoom()
{
}

void GameState_WaitingRoom::handleInput(sf::Time dt)
{
}

void GameState_WaitingRoom::update(sf::Time dt)
{
	// Get all the players info of the game
	std::vector<TankInfo> players = clientConnection->getPlayersInfo(player, gameId, gameState);

	// print inform
	infoText.setString(" There are " + std::to_string(players.size()) + "/4 players");

	if (!players.empty())
	{
		players.erase(players.begin() + player->GetId());
		enemiesMgr->update(dt.asSeconds(), players);
	}
}

void GameState_WaitingRoom::render()
{
	beginDraw();

		// render players and enemies
		player->Render(window);
		enemiesMgr->render(window);

		// Render the text
		window->draw(titleText);
		window->draw(infoText);

	endDraw();
}