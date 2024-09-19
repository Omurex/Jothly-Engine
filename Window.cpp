#include "Window.h"
#include <assert.h>


namespace jothly
{
	Window::Window()
	{
	}


	Window::Window(Vector2i screenSize, const std::string& windowTitle)
	{
		CreateNewWindow(screenSize, windowTitle);
	}


	int Window::CreateNewWindow(Vector2i screenSize, const std::string& windowTitle)
	{
		if (screenSize.x < 1 || screenSize.y < 1)
		{
			return 0;
		}

		_renderWindow.create(sf::VideoMode(screenSize.x, screenSize.y), windowTitle);
		
		return 1;
	}


    bool Window::IsOpen()
    {
        return _renderWindow.isOpen();
    }
}
