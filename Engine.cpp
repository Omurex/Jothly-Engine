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
			sf::Event event;
			while (_window->_renderWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					_window->Close();
			}

			_window->Clear();
			//_window.draw(shape);
			_window->Display();
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

