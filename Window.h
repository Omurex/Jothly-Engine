#pragma once
#include "Vector2i.h"
#include "SFML/Graphics.hpp"


namespace jothly
{
	class Window
	{
		sf::RenderWindow _renderWindow;


		public:

		Window();
		Window(Vector2i screenSize, const std::string& windowTitle);

		int CreateNewWindow(Vector2i screenSize, const std::string& windowTitle);
	};
}