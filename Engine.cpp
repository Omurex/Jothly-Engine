#include "Engine.h"
#include "Window.h"
#include "Vector2.h"


namespace jothly
{
	Engine::Engine()
	{
	}


	Window& Engine::CreateWindow(Vector2i screenSize, const std::string& windowName)
	{
		if (_window != nullptr)
		{
			delete _window;
		}

		_window = new Window(screenSize, windowName);

		return *_window;
	}


	void Engine::RunEngine()
	{
		while (_window->IsOpen())
		{
			/*sf::Event::
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(shape);
			window.display();*/
		}
	}


	Vector2i Engine::GetMousePositionLocal()
	{
		return sf::Mouse::getPosition(_window->_renderWindow);;
	}


	Vector2 Engine::GetMousePositionWorld()
	{
		return Vector2(_window->_renderWindow.mapPixelToCoords(GetMousePositionLocal()));
	}


	Engine::~Engine()
	{
		if (_window != nullptr) delete _window;
	}
}

