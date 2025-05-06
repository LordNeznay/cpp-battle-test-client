#pragma once 

class Vec2
{
public:
	Vec2() = default;

	Vec2(int _x, int _y) :
			x(_x),
			y(_y)
	{}

	int x = 0;
	int y = 0;
};
