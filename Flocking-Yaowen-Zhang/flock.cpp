#include "flock.h"

Flock::Flock() {}

void Flock::draw()
{
	for (VehicleIterator it = flock.begin(); it != flock.end(); it++)
	{
		it->draw();
	}
}

void Flock::flocking(bool isSep, bool isAli, bool isCoh)
{
	for (int i = 0; i < flock.size(); i++)
	{
		sf::Vector2i curBucket = getBucket({flock[i].getPosition().getX(), flock[i].getPosition().getY()});
		flock[i].update();
		sf::Vector2i newBucket = getBucket({flock[i].getPosition().getX(), flock[i].getPosition().getY()});
		if (curBucket != newBucket)
		{
			bucket_remove(curBucket, &flock[i]);
			bucket_add(newBucket, &flock[i]);
		}

		flock[i].run(flockGrid[newBucket.x][newBucket.y], isSep, isAli, isCoh);
	}
}

sf::Vector2i Flock::getBucket(sf::Vector2f pos)
{
	int col = int(pos.x / BUCKET_WIDTH);
	if (col < 0)
	{
		col = 0;
	}
	else if (col >= COLUMNS)
	{
		col = COLUMNS - 1;
	}

	int row = int(pos.y / BUCKET_HEIGHT);
	if (row < 0)
	{
		row = 0;
	}
	else if (row >= ROWS)
	{
		row = ROWS - 1;
	}
	return sf::Vector2i(col, row);
}

void Flock::bucket_add(sf::Vector2i b, Vehicle* obj)
{
	std::vector<Vehicle*> & v = flockGrid[b.x][b.y];

	v.push_back(obj);
}

void Flock::bucket_remove(sf::Vector2i b, Vehicle* obj)
{
	std::vector<Vehicle*> & v = flockGrid[b.x][b.y];

	for (unsigned i = 0; i < v.size(); ++i)
	{
		if (v[i] == obj)
		{
			v.erase(v.begin() + i);
			break;
		}
	}
}

int Flock::getSize() const
{
	return flock.size();
}

Vehicle Flock::getVehicle(int i)
{
	return flock[i];
}

void Flock::addVehicle(Vehicle b)
{
	flock.push_back(b);
}

void Flock::removeVehicle()
{
	if (flock.size() <= 0)
	{
		return;
	}
	flock.pop_back();
}