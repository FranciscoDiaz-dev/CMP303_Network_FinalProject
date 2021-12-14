#include "GUI.h"

#include "ImGUI\imgui.h"
#include "ImGUI-SFML\imgui-SFML.h"

GUI::GUI(sf::RenderWindow* wnd) :
	isActivated(false),
	window(wnd)
{
	ImGui::SFML::Init(*window);
}

GUI::~GUI()
{
	ImGui::SFML::Shutdown(*window); // close ImGui
}

void GUI::processEvent(sf::Event event)
{
	// process ImGui event
	ImGui::SFML::ProcessEvent(*window, event);
}

void GUI::update(sf::Time deltaTime)
{
	ImGui::SFML::Update(*window, deltaTime);
}

void GUI::render()
{
	ImGui::Begin("Sample window"); // begin window							   // Background color edit
		if (ImGui::ColorEdit3("Background color", color)) {
			// this code gets called if color value changes, so
			// the background color is upgraded automatically!
			bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
			bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
			bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
		}

		// Window title text edit
		ImGui::InputText("Window title", windowTitle, 255);

		if (ImGui::Button("Update window title")) {
			// this code gets if user clicks on the button
			// yes, you could have written if(ImGui::InputText(...))
			// but I do this to show how buttons work :)
			window->setTitle(windowTitle);
		}
	ImGui::End(); // end window

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
