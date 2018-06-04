#include "pvector.h"

PVector::PVector() {}

PVector::PVector(float _x, float _y)
{
	x = _x;
	y = _y;
}

void PVector::set(float _x, float _y)
{
	x = _x;
	y = _y;
}

void PVector::setX(float _x)
{
	x = _x;
}

void PVector::setY(float _y)
{
	y = _y;
}

float PVector::getX() 
{
	return x;
}

float PVector::getY()
{
	return y;
}

void PVector::add(PVector vec)
{
	x += vec.x;
	y += vec.y;
}

void PVector::add(float num)
{
	x += num;
	y += num;
}

void PVector::sub(PVector vec)
{
	x -= vec.x;
	y -= vec.y;
}

void PVector::sub(float num)
{
	x -= num;
	y -= num;
}

PVector PVector::sub(PVector vec, PVector vec2)
{
	PVector temp;
	vec.x -= vec2.x;
	vec.y -= vec2.y;
	temp.set(vec.x, vec.y);
	return temp;
}

void PVector::mult(PVector vec)
{
	x *= vec.x;
	y *= vec.y;
}

void PVector::mult(float num)
{
	x *= num;
	y *= num;
}

void PVector::div(PVector vec)
{
	x /= vec.x;
	y /= vec.y;
}

void PVector::div(float num)
{
	x /= num;
	y /= num;
}

void PVector::limit(float max)
{
	float mag = magnitude();

	if (mag > max)
	{
		set(x / mag * max, y / mag * max);
	}
}

float PVector::distance(PVector vec)
{
	float dx = x - vec.x;
	float dy = y - vec.y;
	float dist = sqrt(dx * dx + dy * dy);
	return dist;
}

float PVector::dotProduct(PVector vec) const
{
	float dot = x * vec.x + y * vec.y;
	return dot;
}

float PVector::magnitude() const
{
	return sqrt(x * x + y * y);
}

void PVector::normalize()
{
	float m = magnitude();

	if (m > 0)
	{
		set(x / m, y / m);
	}

	else {
		set(x, y);
	}
}

float PVector::map(float start1, float stop1, float start2, float stop2, float v)
{
	return start2 + (stop2 - start2) * ((v - start1) / (stop1 - start1));
}

float PVector::angleBetween(PVector v1, PVector v2)
{
	float dot = v1.dotProduct(v2);
	float theta = (float)acos(dot / (v1.magnitude() * v2.magnitude()));
	return theta;
}