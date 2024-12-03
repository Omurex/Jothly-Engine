#pragma once
#include "Vector2i.h"
#include "Color.h"
#include "SFML/Graphics.hpp"


namespace jothly
{
	class Color;


	class Window
	{
		friend class Engine;


		sf::RenderWindow _renderWindow;
		Color _backgroundColor;


		#pragma region Should only be called by Engine!
		void Close();

		void Clear();
		void Display();
		#pragma endregion

		public:

		Window();
		Window(Vector2i screenSize, const std::string& windowTitle, const Color& backgroundColor = Color::GREY);

		void SetBackgroundColor(Color backgroundColor) { _backgroundColor = backgroundColor; }

		int CreateNewWindow(Vector2i screenSize, const std::string& windowTitle);

		bool IsOpen();
	};
}