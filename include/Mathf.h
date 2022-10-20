#pragma once

#include <iostream>

class Mathf
{
public:
	Mathf();

	static int Random(int min, int max) {

		return (rand() % (max - min + 1)) + min;
	}

};

struct Vector2f
{
	Vector2f()
		:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
		:x(p_x), y(p_y)
	{}

	void Print()
	{
		std::cout << "(" << x << ", " << y << ")" << std::endl;
	}

	float x, y;
};
