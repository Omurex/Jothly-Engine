#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.h"
#include "Window.h"
#include "Signal.hpp"


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


void TestFunction(int a)
{
	std::cout << a << std::endl;
}


int main()
{
	//SignalSubject a;
	SignalSubject<int> b;
	SignalSubject<int, int> c;
	SignalSubject<int, int, int, int> d;
	SignalSubject<int, std::string> e;

	SignalObserver<int> b_obs;
	SignalObserver<int, int> c_obs;

	// Linker error because doing template stuff in cpp - need to 
	// find way to handle circularly dependency
	b.Register(b_obs);
	//b.Emit(0);

	b_obs.linkedFunction = &TestFunction;
	b_obs.linkedFunction(120);

	b.Emit(99);

	//c_obs.Test(0, 1);

	//b.Register(b_obs); // Works!
	//c.Register(c_obs); // Works!
	//b.Register(c_obs); // THROWS ERROR LETS GO

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