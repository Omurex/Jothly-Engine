#pragma once
#include <string>
#include "Vector2i.h"
#include "Input.h"


namespace jothly
{
	class Window;


	/// <summary>
	/// Handles main game loop and running update / draw on all objects that exist
	/// </summary>
	class Engine
	{
		Input _input = Input();

		Window* _window = nullptr;

		std::string _resourcePath = "./resources/";


		public:

		Engine();
		~Engine();


		Window& CreateWindow(Vector2i screenSize, const std::string& windowName);

		Vector2i GetMousePositionLocal();
		Vector2 GetMousePositionWorld();
	};
}