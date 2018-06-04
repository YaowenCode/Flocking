#define _USE_MATH_DEFINES
#include "vehicle.h"

Vehicle::Vehicle(PVector pos)
{
	angle = (rand() % 360) * 3.14f / 180.f;
	acceleration = PVector(0,0);
	velocity = PVector(cos(angle) / 10, sin(angle) / 10);
	position = pos;
	radius = 15;
	maxspeed = 3;
	maxforce = 1;

	desiredSep = 50;
	desiredAli = 70;
	desiredCoh = 30;
	sepWeight = 1.5;
	aliWeight = 1.5;
	cohWeight = 1.0;

	triangle.setPointCount(3);
	triangle.setPoint(0, sf::Vector2f(radius, 0));
	triangle.setPoint(1, sf::Vector2f(radius * 0.5, radius * 1.866));
	triangle.setPoint(2, sf::Vector2f(radius * 1.5, radius * 1.866));
	triangle.setFillColor(sf::Color::Red);
	triangle.setOutlineColor(sf::Color::White);
	triangle.setOutlineThickness(1);
	triangle.setOrigin(radius, radius);
	triangle.setRotation(angle);
	triangle.setPosition(pos.getX(), pos.getY());
}

void Vehicle::update()
{
	velocity.add(acceleration);
	velocity.limit(maxspeed);
	position.add(velocity);
	acceleration.mult(.0);
	angle = static_cast<float>(atan2(velocity.getX(), -velocity.getY()) * 180 / M_PI);
	triangle.setRotation(angle);
	triangle.setPosition(position.getX(), position.getY());
}

void Vehicle::draw()
{
	window.draw(triangle);
}

void Vehicle::applyForce(PVector force)
{
	acceleration.add(force);
}

void Vehicle::run(std::vector<Vehicle*> vehicles, bool isSep, bool isAli, bool isCoh)
{
	flock(vehicles, isSep, isAli, isCoh);
	update();
	borders();
}

void Vehicle::flock(std::vector<Vehicle*> vehicles, bool isSep, bool isAli, bool isCoh)
{
	PVector sep = separate(vehicles);
	PVector ali = align(vehicles);
	PVector coh = cohesion(vehicles);

	sep.mult(sepWeight);
	ali.mult(aliWeight);
	coh.mult(cohWeight);

	if (isSep) applyForce(sep);
	if (isAli) applyForce(ali);
	if (isCoh) applyForce(coh);
}

void Vehicle::borders()
{
	if (position.getX() < 0)    position.setX(position.getX() + 1600);
	if (position.getY() < 0)    position.setY(position.getY() + 900);
	if (position.getX() > 1600) position.setX(position.getX() - 1600);
	if (position.getY() > 900) position.setY(position.getY() - 900);
}

void Vehicle::arrive(PVector target)
{
	PVector desired = PVector::sub(target, position);

	float d = desired.magnitude();
	desired.normalize();
	if (d < 100)
	{
		float m = PVector::map(100, 0, d, 0, maxspeed);
		desired.mult(m);
	}
	else 
	{
		desired.mult(maxspeed);
	}

	PVector steer = PVector::sub(desired, velocity);
	steer.limit(maxforce);
	applyForce(steer);
}

PVector Vehicle::seek(PVector target)
{
	PVector desired = PVector::sub(target, position);
	desired.normalize();
	desired.mult(maxspeed);
	PVector steer = PVector::sub(desired, velocity);
	steer.limit(maxforce);
	
	return steer;
}

PVector Vehicle::separate(std::vector<Vehicle*> vehicles)
{
	float desiredseparation = desiredSep;
	PVector steer(0, 0);
	int count = 0;

	for (int i = 0; i < vehicles.size(); i++)
	{
		float d = position.distance(vehicles[i]->position);

		if ((d > 0) && (d < desiredseparation))
		{
			PVector diff(0, 0);
			diff = diff.sub(position, vehicles[i]->position);
			diff.normalize();
			diff.div(d);
			steer.add(diff);
			count++;
		}
	}

	if (count > 0)
	{
		steer.div(static_cast<float>(count));
	}

	if (steer.magnitude() > 0)
	{
		steer.normalize();
		steer.mult(maxspeed);
		steer.sub(velocity);
		steer.limit(maxforce);
	}

	return steer;
}

PVector Vehicle::align(std::vector<Vehicle*> vehicles)
{
	float neighbordist = desiredAli;
	PVector sum = PVector(0, 0);
	int count = 0;
	for (Vehicle* other : vehicles) 
	{
		float d = position.distance(other->position);
		if ((d > 0) && (d < neighbordist)) 
		{
			sum.add(other->velocity);
			count++;
		}
	}
	if (count > 0) 
	{
		sum.div(count);
		sum.normalize();
		sum.mult(maxspeed);
		PVector steer = PVector::sub(sum, velocity);
		steer.limit(maxforce);
		return steer;
	}
	else 
	{
		return PVector(0, 0);
	}
}

PVector Vehicle::cohesion(std::vector<Vehicle*> vehicles)
{
	float neighbordist = desiredCoh;
	PVector sum = PVector(0, 0);
	int count = 0;
	for (Vehicle* other : vehicles) 
	{
		float d = position.distance(other->position);
		if ((d > 0) && (d < neighbordist))
		{
			sum.add(other->position);
			count++;
		}
	}
	if (count > 0) 
	{
		sum.div(count);
		return seek(sum);
	}
	else 
	{
		return PVector(0, 0);
	}
}

PVector Vehicle::getPosition()
{
	return position;
}

float Vehicle::getDesiredSep() const { return desiredSep; }

float Vehicle::getDesiredAli() const { return desiredAli; }

float Vehicle::getDesiredCoh() const { return desiredCoh; }

float Vehicle::getSepWeight() const { return sepWeight; }

float Vehicle::getAliWeight() const { return aliWeight; }

float Vehicle::getCohWeight() const { return cohWeight; }

void Vehicle::setDesiredSep(float n) { desiredSep = n; }

void Vehicle::setDesiredAli(float n) { desiredAli = n; }

void Vehicle::setDesiredCoh(float n) { desiredCoh = n; }

void Vehicle::setSepWeight(float n) { sepWeight = n; }

void Vehicle::setAliWeight(float n) { aliWeight = n; }

void Vehicle::setCohWeight(float n) { cohWeight = n; }