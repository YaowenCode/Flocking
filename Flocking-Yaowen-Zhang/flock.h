#pragma once
#include"vehicle.h"

#ifndef FLOCK_H
#define FLOCK_H

typedef std::vector<Vehicle>::iterator VehicleIterator;
const float BUCKET_WIDTH = 100;
const float BUCKET_HEIGHT = 100;
const int COLUMNS = 16;
const int ROWS = 9;

class Flock 
{
private:
	std::vector<Vehicle> flock;
	std::vector<Vehicle*> flockGrid[COLUMNS][ROWS];
public:
	Flock();
	int getSize() const;
	Vehicle getVehicle(int i);
	void flocking(bool isSep, bool isAli, bool isCoh);
	void draw();
	sf::Vector2i getBucket(sf::Vector2f pos);
	void bucket_add(sf::Vector2i b, Vehicle* obj);
	void bucket_remove(sf::Vector2i b, Vehicle* obj);
	void addVehicle(Vehicle b);
	void removeVehicle();
};

#endif // !FLOCK_H