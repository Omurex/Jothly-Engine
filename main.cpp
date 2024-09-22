#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.h"
#include "Window.h"
#include "SignalSubject.h"


using namespace jothly;


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
	//SignalSubject a;
	SignalSubject<int> b;
	SignalSubject<int, int> c;
	SignalSubject<int, int, int, int> d;
	SignalSubject<int, std::string> e;

	//b.DoSomething(3).size();

	//std::cout << d.sum(1, 2, 3, 4) << std::endl;

	//a.DoSomething();
	/*b.DoSomething(1);
	c.DoSomething(2, 3);
	d.DoSomething(3, "hi");*/
	
	
	
	
	
	
	
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