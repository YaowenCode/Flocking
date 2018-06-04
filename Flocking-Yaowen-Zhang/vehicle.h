#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "pvector.h"

#ifndef VEHICLE_H
#define VEHICLE_H

extern sf::RenderWindow window;

class Vehicle
{
private:
	PVector position;
	PVector velocity;
	PVector acceleration;
	sf::ConvexShape triangle;
	float angle;
	float maxspeed;
	float maxforce;
	float radius;
	float desiredSep;
	float desiredAli;
	float desiredCoh;
	float sepWeight;
	float aliWeight;
	float cohWeight;
public:
	Vehicle(PVector pos);
	void update();
	void draw();
	void applyForce(PVector force);
	void arrive(PVector target);
	void run(std::vector<Vehicle*> vehicles, bool isSep, bool isAli, bool isCoh);
	void flock(std::vector<Vehicle*> vehicles, bool isSep, bool isAli, bool isCoh);
	void borders();
	PVector seek(PVector target);
	PVector separate(std::vector<Vehicle*> vehicles);
	PVector align(std::vector<Vehicle*> vehicles);
	PVector cohesion(std::vector<Vehicle*> vehicles);
	PVector getPosition();
	float getDesiredSep() const;
	float getDesiredAli() const;
	float getDesiredCoh() const;
	float getSepWeight() const;
	float getAliWeight() const;
	float getCohWeight() const;
	void setDesiredSep(float n);
	void setDesiredAli(float n);
	void setDesiredCoh(float n);
	void setSepWeight(float n);
	void setAliWeight(float n);
	void setCohWeight(float n);
};

#endif // !VEHICLE_H
