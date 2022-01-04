#include "GameState_Selection.h"

#include "Framework/Input.h"
#include "NetworkSimulator.h"

GameState_Selection::GameState_Selection(GameStateManager* stateMgr) : GameStateBase(stateMgr)
{
	// initialise font and text
	montserratFont.loadFromFile("Assets/Montserrat-Regular.ttf");
	infoText.setFont(montserratFont);
	infoText.setOutlineColor(sf::Color::Black);
	infoText.setOutlineThickness(1.f);
	infoText.setString("Waiting for other players");
	instructionsText.setFont(montserratFont);
	instructionsText.setOutlineColor(sf::Color::Black);
	instructionsText.setOutlineThickness(1.f);
	instructionsText.setString("Introduce:\n player name, \n select server \n and player colour.");
	instructionsText.setPosition(window->getView().getCenter()/2.0f);

	// get the objects to use on this class from the shared context
	player = gameStateManager->getSharedContext()->player;

	// Declare our ImGui
	gui = new GUI(stateMgr);
	// save the gui in the shared context
	gameStateManager->getSharedContext()->gui = gui;
}

GameState_Selection::~GameState_Selection()
{
	delete gui;
	gui = nullptr;
}

void GameState_Selection::handleInput(sf::Time dt)
{
	// check if the user want to pause the game
	if (input->isKeyDown(sf::Keyboard::P))
	{
		input->setKeyUp(sf::Keyboard::P);

		printf("\n\n--------PLAY--------\n\n");

		gameStateManager->switchTo(GState::LEVEL);
	}
}

void GameState_Selection::update(sf::Time dt)
{
	// Update text
	//infoText.setString("Waiting for other players. Current players: " + );
	//infoText.setString("Game Time: " + Utils::stringify(netSimulator->Time()));

	// update gui
	gui->update(dt);
}

void GameState_Selection::render()
{
	beginDraw();

	// Render the text
	window->draw(infoText);
	window->draw(instructionsText);

	// Render the Gui
	gui->render();

	endDraw();
}