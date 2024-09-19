#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.h"
#include "Window.h"


void TemplateFunction()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Works!
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			std::cout << "MOVE RIGHT" << std::endl;
		}
		else
		{
			std::cout << " " << std::endl;
		}*/


		window.clear();
		window.draw(shape);
		window.display();
	}
}


int main()
{
	TemplateFunction();

	jothly::Engine engine;
	jothly::Window& window = engine.CreateWindow(jothly::Vector2i(200, 200), "Engine works!");

	/*while (window.IsOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}*/

	return 0;
}