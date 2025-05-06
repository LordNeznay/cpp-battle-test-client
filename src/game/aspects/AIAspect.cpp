#include "AIAspect.hpp"
#include "game/base/Unit.hpp"

void aspect::AI::Think(Unit& unit, GameWorld& world)
{
	if (mImpl && unit.isAlive())
	{
		mImpl->Think(unit, world);
	}
}
