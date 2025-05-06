#include "Map.hpp"

Map::Map(int w, int h) :
	mWidth(w),
	mHeight(h)
{

}

int Map::getWidth() const
{
	return mWidth;
}

int Map::getHeight() const
{
	return mHeight;
}
