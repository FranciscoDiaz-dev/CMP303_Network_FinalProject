#include "GUI.h"

// Including the ImGui files
#include "ImGUI\imgui.h"
#include "ImGUI-SFML\imgui-SFML.h"
#include "ImGUI\misc\cpp\imgui_stdlib.h"

#include "..\..\NetworkFramework\ServersListManager.h"
#include "..\..\NetworkFramework\ServerConnection.h"


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


GUI::GUI(SharedContext* sharedCtxt)
	: selectedServerIndex(0), sharedContext(sharedCtxt)
{

	window = sharedContext->window;
	serversListMgr = sharedContext->serversListMgr;

	// get the list of servers available
	servers = serversListMgr->getServersList();

	// init GUI
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
	ImGui::Begin("Server Settings"); // begin window

		// Show Selected Server Details
		ServerInfo selectedServerInfo = serversListMgr->getServerInfoById(servers.at(selectedServerIndex));


		// Show list for choosing server if it has not already been choosen
		if (sharedContext->serverConnection == nullptr)
		{
			//Title
			ImGui::Text("Choose a server:");

			// Show List Server
			if (ImGui::Combo("Servers", &selectedServerIndex, servers))
			{
			}
			int sendUpdateRate = selectedServerInfo.sendUpdateRate;
			if (ImGui::InputInt("Send Update Rate (ms)", &sendUpdateRate))
			{
				selectedServerInfo.sendUpdateRate = sendUpdateRate;
				serversListMgr->updateServerInfoById(servers.at(selectedServerIndex), selectedServerInfo);
			}
			int fakeLatency = selectedServerInfo.fakeLatency;
			if (ImGui::InputInt("Fake Latency (ms)", &fakeLatency))
			{
				selectedServerInfo.fakeLatency = fakeLatency;
				serversListMgr->updateServerInfoById(servers.at(selectedServerIndex), selectedServerInfo);
			}
		}


		if (selectedServerInfo.name != "")
		{
			ImGui::Text("\n");
			ImGui::Text("*Server Details*");
			ImGui::Text(string("Name: " + selectedServerInfo.name).c_str());
			ImGui::Text(string("IP: " + selectedServerInfo.ipAddr.toString()).c_str());
			ImGui::Text("UDP Port: %d", selectedServerInfo.udpPort);
			ImGui::Text("TCP Listener Port: %d", selectedServerInfo.tcpListenerPort);
			ImGui::Text("Max games can host: %d", selectedServerInfo.maxNumGames);
			ImGui::Text("Max players per games can host: %d", selectedServerInfo.maxNumPlayersPerGame);
			ImGui::Text("Send Update Rate: %d ms", int(selectedServerInfo.sendUpdateRate));
			ImGui::Text("Fake Latency Send Update: %d ms", int(selectedServerInfo.fakeLatency));
			ImGui::Text("Send Update Period (Rate + Latency): %d ms", int(selectedServerInfo.sendUpdateRate + selectedServerInfo.fakeLatency));
			if(sharedContext->serverConnection != nullptr)
				ImGui::Text("Status: Running");
			ImGui::Text("\n");
		}

		// Run the selected server
		if (sharedContext->serverConnection == nullptr && ImGui::Button("Run"))
		{
			sharedContext->serverConnection = new ServerConnection(servers.at(selectedServerIndex), selectedServerInfo);
		}
		// Stop the selected server
		else if (sharedContext->serverConnection != nullptr && ImGui::Button("Stop"))
		{
			delete sharedContext->serverConnection;
			sharedContext->serverConnection = nullptr;
		}

	ImGui::End(); // end window

	// render the window
	ImGui::SFML::Render(*window);
}