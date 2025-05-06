#include "Unit.hpp"
#include "game/aspects/MovementTargetAspect.hpp"
#include "game/aspects/DeathStatusAspect.hpp"

UnitId Unit::getId() const
{
	return mId;
}

void Unit::marchStart(Vec2 targetPos) {
	auto data = getAspect<aspect::MovementTarget>();
	if (not data)
	{
		data = addAspect(aspect::MovementTarget{});
	}

	data->mTargetPos = targetPos;
}

bool Unit::isAlive() const {
	if (auto death = getAspect<aspect::DeathStatus>())
	{
		return not death->mIsDead;
	}

	return true;
}
