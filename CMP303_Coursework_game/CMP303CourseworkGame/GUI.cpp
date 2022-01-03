#include "GUI.h"

// Including the ImGui files
#include "ImGUI\imgui.h"
#include "ImGUI-SFML\imgui-SFML.h"
#include "ImGUI\misc\cpp\imgui_stdlib.h"

#include "SharedContext.h"
#include "ServersManager.h"
#include "Tank.h"


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


GUI::GUI(sf::RenderWindow* wnd, SharedContext* sharedContxt) :
	isActivated(false),
	window(wnd),
	sharedContext(sharedContxt),
	selectedServerIndex(0)
{
	ImGui::SFML::Init(*window);

	// get the list of servers available
	servers = sharedContext->serversManager->getServersList();
	selectedServerInfo = sharedContext->serversManager->getServerInfoById(servers.at(selectedServerIndex));
	tankColours = {"black", "blue", "green", "red"}; // tank colours available
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

		// Player Name
		// Input
		if (sharedContext->player != nullptr)
		{
			std::string playerName = sharedContext->player->GetPlayerName();
			ImGui::InputText("Player Name", &playerName);

			// Button
			if (ImGui::Button("Apply Name"))
			{
				window->setTitle(playerName);
			}
		}

		// Choosing Server
		if (ImGui::Combo("Server", &selectedServerIndex, servers))
		{
			//update selected server info to show
			selectedServerInfo = sharedContext->serversManager->getServerInfoById(servers.at(selectedServerIndex));

		}

		// Choosing Colour of the Tank
		if (ImGui::Combo("Tank Colour", &selectedColourIndex, tankColours))
		{
			if (tankColours.at(selectedColourIndex) != sharedContext->player->GetColour())
			{
				sharedContext->player->SetColour(tankColours.at(selectedColourIndex));
			}
		}
	ImGui::End(); // end window

	// render the window
	ImGui::SFML::Render(*window);
}


void GUI::active()
{
	isActivated = true;
}

void GUI::deactive()
{
	isActivated = false;
}
