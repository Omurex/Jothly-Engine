#pragma once
#include <string>
#include "Vector2.h"
#include "Window.h"


namespace jothly
{
	/// <summary>
	/// Handles main game loop and running update / draw on all objects that exist
	/// </summary>
	class Engine
	{
		Window* _window = nullptr;

		std::string _resourcePath = "./resources/";


		public:

		Engine(Window& window);
		Engine(Vector2 screenSize);
	};
}