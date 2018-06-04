#include "VehicleSystem.h"
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

sf::RenderWindow window;

VehicleSystem::VehicleSystem()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Yaowen's Flocking");

	font.loadFromFile("arial.ttf");

	fps = 0;
	isSep = false;
	isAli = false;
	isCoh = false;

	fpsCount.setFont(font);
	fpsCount.setFillColor(sf::Color::White);
	fpsCount.setCharacterSize(30);
	fpsCount.setPosition(100, 50);

	vehicleCount.setFont(font);
	vehicleCount.setFillColor(sf::Color::White);
	vehicleCount.setCharacterSize(30);
	vehicleCount.setPosition(100, 100);

	sepStatus.setFont(font);
	sepStatus.setFillColor(sf::Color::White);
	sepStatus.setCharacterSize(30);
	sepStatus.setPosition(100, 150);

	aliStatus.setFont(font);
	aliStatus.setFillColor(sf::Color::White);
	aliStatus.setCharacterSize(30);
	aliStatus.setPosition(100, 200);

	cohStatus.setFont(font);
	cohStatus.setFillColor(sf::Color::White);
	cohStatus.setCharacterSize(30);
	cohStatus.setPosition(100, 250);
}

void VehicleSystem::run()
{
	sf::Clock clock;

	float dt = clock.restart().asSeconds();

	while (window.isOpen())
	{
		fps = 1 / clock.restart().asSeconds();
		Input();
		window.clear();
		update();
		draw();
		window.display();
	}
}

void VehicleSystem::update()
{
	fpsCount.setString("Frames per Second: " + std::to_string(int(fps)));
	vehicleCount.setString("Total Boid Count: " + std::to_string(flock.getSize()));
	if (isSep)
	{
		sepStatus.setString("Separation On");
	}
	else
	{
		sepStatus.setString("Separation Off");
	}
	if (isAli)
	{
		aliStatus.setString("Alignment On");
	}
	else
	{
		aliStatus.setString("Alignment Off");
	}
	if (isCoh)
	{
		cohStatus.setString("Cohesion On");
	}
	else
	{
		cohStatus.setString("Cohesion Off");
	}

	flock.flocking(isSep, isAli, isCoh);
}

void VehicleSystem::draw()
{
	flock.draw();
	window.draw(fpsCount);
	window.draw(vehicleCount);
	window.draw(sepStatus);
	window.draw(aliStatus);
	window.draw(cohStatus);
}

void VehicleSystem::Input()

{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mouse = sf::Mouse::getPosition(window);

			Vehicle v(PVector((float)mouse.x, (float)mouse.y));
			flock.addVehicle(v);
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
		{
			Vehicle v = Vehicle(PVector(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT));
			flock.addVehicle(v);
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
		{
			flock.removeVehicle();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
		{
			isSep = (isSep == false) ? true : false;
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
		{
			isAli = (isAli == false) ? true : false;
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
		{
			isCoh = (isCoh == false) ? true : false;
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
		{
			flock.removeVehicle();
		}
	}
}