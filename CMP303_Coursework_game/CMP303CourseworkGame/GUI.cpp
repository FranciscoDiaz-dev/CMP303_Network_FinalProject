#include "GUI.h"

// Including the ImGui files
#include "ImGUI\imgui.h"
#include "ImGUI-SFML\imgui-SFML.h"
#include "ImGUI\misc\cpp\imgui_stdlib.h"

#include "SharedContext.h"
#include "..\..\NetworkFramework\ServersManager.h"
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


GUI::GUI(GameStateManager* gameStateManager) :
	selectedServerIndex(0),
	selectedColourIndex(0),
	gameStateMgr(gameStateManager)
{
	// get the list of servers available
	window = gameStateMgr->getSharedContext()->window;
	serversMgr = gameStateMgr->getSharedContext()->serversManager;
	player = gameStateMgr->getSharedContext()->player;
	gameId = gameStateMgr->getSharedContext()->gameId;
	clientConnection = gameStateMgr->getSharedContext()->clientConnection;

	// update server list
	servers = serversMgr->getServersList();
	playerColours = {"black", "blue", "green", "red"}; // player colours available

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
}

void GUI::render()
{
	ImGui::Begin("Game Settings"); // begin window

		// Choosing Server
		if (ImGui::Combo("Server", &selectedServerIndex, servers))
		{
		}

		// Choosing Colour of the Tank
		if (ImGui::Combo("Tank Colour", &selectedColourIndex, playerColours))
		{
		}

		if (ImGui::Button("Find a game"))
		{
			// Apply colour
			if (playerColours.at(selectedColourIndex) != player->GetColour())
			{
				player->SetColour(playerColours.at(selectedColourIndex));
			}

			// Apply selected server
			serversMgr->selectServer(servers.at(selectedServerIndex));

			PlayerMessage playerMsg;
			playerMsg.gameId = *gameId;
			playerMsg.playerInfo = player->getPlayerInfo();

			bool joined = clientConnection->joinAGame(&playerMsg, serversMgr->getSelectedServer().sockAddr);

			if (joined)
				gameStateMgr->switchTo(GState::LEVEL);
		}

	ImGui::End(); // end window

	// render the window
	ImGui::SFML::Render(*window);
}