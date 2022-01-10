#include "GameState_Selection.h"

#include "..\..\NetworkFramework\ClientConnection.h"
#include "Framework/Input.h"
#include "Tank.h"
#include "GUI.h"

GameState_Selection::GameState_Selection(GameStateManager* stateMgr) : GameStateBase(stateMgr)
{
	// initialise text strings
	titleText.setString(" Selection");
	infoText.setString(" Select options and find a game.");

	// get the objects to use on this class from the shared context
	player = gameStateMgr->getSharedContext()->player;
	player->Reset(); // make sure the player does not contain any old information

	// Declare our ImGui
	// save the gui in the shared context
	gui = new GUI(stateMgr);
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