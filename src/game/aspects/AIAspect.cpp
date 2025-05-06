#include "AIAspect.hpp"
#include "game/base/Unit.hpp"

void aspect::AI::Think(Unit& unit, GameWorld& world)
{
	if (mImpl && unit.isAlive())
	{
		mImpl->Think(unit, world);
	}
}

bool aspect::AI::canAct(const Unit& unit, const GameWorld& world) const {
	if (mImpl && unit.isAlive())
	{
		return mImpl->canAct(unit, world);
	}

	return false;
}
