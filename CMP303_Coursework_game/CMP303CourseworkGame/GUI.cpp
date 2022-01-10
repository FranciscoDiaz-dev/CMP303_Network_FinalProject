#include "GUI.h"

// Including the ImGui files
#include "ImGUI\imgui.h"
#include "ImGUI-SFML\imgui-SFML.h"
#include "ImGUI\misc\cpp\imgui_stdlib.h"

#include "SharedContext.h"
#include "..\..\NetworkFramework\ServersListManager.h"
#include "..\..\NetworkFramework\ClientConnection.h"
#include "Tank.h"
#include "GameStateManager.h"


// Redefine callbackCombo and ListBox to use std::vector<std::string> instead arrays of const char
// Code provided by @EliasDaler on "Using ImGui with modern C++ and STL for creating awesome game dev tools. Part 2. Some tips and tricks."
// Link: https://eliasdaler.github.io/using-imgui-with-sfml-pt2/
namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

}


GUI::GUI(GameStateManager* gameStateMgr) :
	selectedServerIndex(0),
	selectedColourIndex(0),
	textTimeout(0.0f),
	gameStateMgr(gameStateMgr)
{
	// get the list of servers available
	window = gameStateMgr->getSharedContext()->window;
	serversListMgr = gameStateMgr->getSharedContext()->serversListMgr;
	player = gameStateMgr->getSharedContext()->player;
	gameId = gameStateMgr->getSharedContext()->gameId;
	gameState = gameStateMgr->getSharedContext()->gameState;
	clientConnection = gameStateMgr->getSharedContext()->clientConnection;

	// get servers list
	serversList = serversListMgr->getServersList();

	// update player colour by default
	playerColours = {"black", "blue", "green", "red"}; // player colours available
	player->SetTexture(playerColours.at(selectedColourIndex));

	// Update the player position
	player->SetPosition(sf::Vector2f(450.0f, 300.0f));

	ImGui::SFML::Init(*window);
}

GUI::~GUI()
{
	ImGui::SFML::Shutdown(*window); // close ImGui
}


void GUI::processEvent(sf::Event event)
{
	ImGui::SFML::ProcessEvent(*window, event);
}

void GUI::update(sf::Time deltaTime)
{
	ImGui::SFML::Update(*window, deltaTime);

	// substract time passed
	if (textTimeout > 0.0f)
		textTimeout -= deltaTime.asSeconds();
}

void GUI::render()
{
	ImGui::Begin("Game Settings"); // begin window

		// Choosing Server
		if (ImGui::Combo("Server", &selectedServerIndex, serversList))
		{
		}

		// Choosing Colour of the Tank
		if (ImGui::Combo("Tank Colour", &selectedColourIndex, playerColours))
		{
			// Apply colour to the player
			if (playerColours.at(selectedColourIndex) != player->GetColour())
			{
				player->SetTexture(playerColours.at(selectedColourIndex));
			}
		}

		bool isBot = player->GetIsBot();
		if (ImGui::Checkbox("Is a bot", &isBot))
		{
			// if the new value is different from the one it currently has then change it
			if (isBot != player->GetIsBot())
			{
				player->SetIsBot(isBot);
			}
		}

		if (textTimeout <= 0.0f && ImGui::Button("Find a game"))
		{

			// Get and apply the selected server
			ServerInfo selectedServerInfo = serversListMgr->getServerInfoById(serversList.at(selectedServerIndex));

			if (clientConnection->joinAGame(selectedServerInfo))
			{
				// go to the game
				gameStateMgr->switchTo(GState::LEVEL);
				gameStateMgr->addToRemoveContainer(GState::SELECTION);
			}
			else
			{
				timeoutText = "\nServer unnavailable, \nplease try later: %ds.";
				textTimeout = 10.0f; // seconds
			}
		}

		if (textTimeout > 0.0f)
			ImGui::Text(timeoutText.c_str(), int(textTimeout));

	ImGui::End(); // end window

	// render the window
	ImGui::SFML::Render(*window);
}