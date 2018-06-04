#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "flock.h"

#ifndef VEHICLESYSTEM_H
#define VEHICLESYSTEM_H

class VehicleSystem 
{
private:
	sf::Text fpsCount;
	sf::Text vehicleCount;
	sf::Text sepStatus;
	sf::Text aliStatus;
	sf::Text cohStatus;
	sf::Font font;
	Flock flock;
	float fps;
	bool isSep;
	bool isAli;
	bool isCoh;
	void Input();
public:
	VehicleSystem();
	void run();
	void update();
	void draw();
};

#endif // !VEHICLESYSTEM_H