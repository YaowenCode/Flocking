#pragma once
#include <math.h>

#ifndef PVECTOR_H
#define PVECTOR_H

class PVector
{
private:
	float x;
	float y;
public:
	PVector();
	PVector(float _x, float _y);
	void set(float _x, float _y);
	float getX();
	float getY();
	void setX(float _x);
	void setY(float _y);
	void add(PVector vec);
	void add(float num);
	void sub(PVector vec);
	void sub(float num);
	static PVector PVector::sub(PVector vec, PVector vec2);
	void mult(PVector vec);
	void mult(float num);
	void div(PVector vec);
	void div(float num);
	void limit(float max);
	float distance(PVector vec);
	float dotProduct(PVector vec) const;
	float magnitude() const;
	void normalize();
	static float map(float start1, float stop1, float start2, float stop2, float v);
	static float angleBetween(PVector v1, PVector v2);
};

#endif // !PVECTOR_H
