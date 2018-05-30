#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

#ifndef VEHICLE_H
#define VEHICLE_H

extern sf::RenderWindow window;

class Vehicle
{
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float maxspeed;
	float maxforce;
	float radius;
	
public:
	sf::RectangleShape shape;
	Vehicle(sf::Vector2f pos);
	void addForce(sf::Vector2f force);
	void seek(sf::Vector2f target);
	void update(float dt);
	void draw();
};

#endif // !VEHICLE_H
