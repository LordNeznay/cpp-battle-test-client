#pragma once 

class Vec2
{
public:
	Vec2() = default;

	Vec2(int _x, int _y) :
			x(_x),
			y(_y)
	{}

	bool operator==(const Vec2& other) 
	{ 
		return x == other.x && y == other.y; 
	}

	bool operator!=(const Vec2& other)
	{
		return not(*this == other);
	}

public:
	int x = 0;
	int y = 0;
};
