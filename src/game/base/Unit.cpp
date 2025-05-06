#include "Unit.hpp"
#include "game/aspects/MovementTargetAspect.hpp"

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
