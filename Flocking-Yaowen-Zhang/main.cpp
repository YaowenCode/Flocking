#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "vehicle.h"

sf::RenderWindow window;

int main()
{
	window.create(sf::VideoMode(1600, 900), "Yaowen's Flocking");

	sf::Clock clock;

	Vehicle v({ 400,300 });

	float dt = clock.restart().asSeconds();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		v.seek({ 800,800 });
		v.update(dt);
		v.draw();
		window.display();
	}

	return 0;
}