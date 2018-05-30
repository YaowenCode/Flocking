#include "vehicle.h"

Vehicle::Vehicle(sf::Vector2f pos)
{
	acceleration = { 0,0 };
	velocity = { 0,0 };
	position = { pos.x, pos.y };
	radius = 5;
	maxspeed = 5;
	maxforce = 0.1;
	shape.setFillColor(sf::Color::Blue);
	shape.setSize({ 50, 30 });
	shape.setPosition(position);
}

void Vehicle::update(float dt)
{
	if (sqrt(velocity.x * velocity.x + velocity.y * velocity.y ) < maxspeed)
	{
		velocity += acceleration;
	}
	position += velocity * dt;
	shape.setPosition(position);
}

void Vehicle::addForce(sf::Vector2f force)
{
	acceleration += force;
}

void Vehicle::seek(sf::Vector2f target)
{
	sf::Vector2f desired = target - position;
	desired = desired / sqrt(desired.x * desired.x + desired.y * desired.y);
	desired = desired * maxspeed;
	sf::Vector2f steer = desired - velocity;
	if (sqrt(steer.x * steer.x + steer.y * steer.y) < maxforce)
	{
		addForce(steer);
	}
}

void Vehicle::draw()
{
	window.draw(shape);
}