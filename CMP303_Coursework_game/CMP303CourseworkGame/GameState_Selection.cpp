#include "GameState_Selection.h"

#include "Framework/Input.h"
#include "NetworkSimulator.h"

GameState_Selection::GameState_Selection(GameStateManager* stateMgr) : GameStateBase(stateMgr)
{
	// initialise font and text
	montserratFont.loadFromFile("Assets/Montserrat-Regular.ttf");

	titleText.setFont(montserratFont);
	titleText.setOutlineColor(sf::Color::Black);
	titleText.setOutlineThickness(1.f);
	titleText.setString(" Selection");

	infoText.setFont(montserratFont);
	infoText.setOutlineColor(sf::Color::Black);
	infoText.setOutlineThickness(1.f);
	infoText.setCharacterSize(20);
	infoText.setString(" Select options and find a game.");
	infoText.setPosition(sf::Vector2f(titleText.getPosition().x + 300.0f, titleText.getPosition().y + 50.0f));

	// get the objects to use on this class from the shared context
	player = gameStateMgr->getSharedContext()->player;
	player->Reset(); // make sure the player does not contain any old information

	// Declare our ImGui
	gui = new GUI(stateMgr);
	// save the gui in the shared context
	gameStateMgr->getSharedContext()->gui = gui;
}

GameState_Selection::~GameState_Selection()
{
	delete gui;
	gui = nullptr;
}

void GameState_Selection::handleInput(sf::Time dt)
{
}

void GameState_Selection::update(sf::Time dt)
{
	// update gui
	gui->update(dt);
}

void GameState_Selection::render()
{
	beginDraw();

	// Render the text
	window->draw(titleText);
	window->draw(infoText);

	// render
	player->Render(window);

	// Render the Gui
	gui->render();

	endDraw();
}