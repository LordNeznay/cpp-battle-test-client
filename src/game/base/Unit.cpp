#include "Unit.hpp"
#include "game/base/GameWorld.hpp"
#include "game/aspects/MovementTargetAspect.hpp"
#include "game/aspects/DeathStatusAspect.hpp"
#include "game/aspects/PositionAspect.hpp"
#include "game/aspects/AIAspect.hpp"

#include "IO/System/EventLog.hpp"
#include "IO/Events/MarchStarted.hpp"

UnitId Unit::getId() const
{
	return mId;
}

void Unit::marchStart(GameWorld& world, Vec2 targetPos) {
	auto data = getAspect<aspect::MovementTarget>();
	if (not data)
	{
		data = addAspect(aspect::MovementTarget{});
	}

	data->mTargetPos = targetPos;

	auto currentPosData = getAspect<aspect::Position>();
	Vec2 currentPos = currentPosData ? currentPosData->getPosition() : Vec2();

	if (auto logger = world.getEventLogger())
	{
		logger->log(
			world.getSimulationStep(),
			sw::io::MarchStarted{
				getId(), (uint32_t)currentPos.x, (uint32_t)currentPos.y, (uint32_t)targetPos.x, (uint32_t)targetPos.y});
	}
}

bool Unit::isAlive() const {
	if (auto death = getAspect<aspect::DeathStatus>())
	{
		return not death->mIsDead;
	}

	return true;
}

bool Unit::canActOnNextStep(const GameWorld& world) const {
	if (auto unitAI = getAspect<aspect::AI>())
	{
		return unitAI->canAct(*this, world);
	}

	return false;
}
