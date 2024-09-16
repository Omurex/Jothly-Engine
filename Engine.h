#pragma once
#include "Window.h"


namespace jothly
{
	/// <summary>
	/// Handles main game loop and running update / draw on all objects that exist
	/// </summary>
	class Engine
	{
		Window* window = nullptr;


		public:
		Engine(Window& window);
		Engine();
	};
}