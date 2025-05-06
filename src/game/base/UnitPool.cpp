#include "UnitPool.hpp"

#include "game/base/GameWorld.hpp"
#include "game/aspects/DeathStatusAspect.hpp"

#include "IO/System/EventLog.hpp"
#include "IO/Events/UnitDied.hpp"

Unit& UnitPool::spawnUnit(UnitId unitId)
{
	mStorage.emplace_back(std::make_unique<Unit>());
	auto& unit = mStorage.back();

	unit->mId = unitId;

	return *unit;
}

void UnitPool::removeDeathUnits(GameWorld& world)
{
	auto from = std::remove_if(
		mStorage.begin(),
		mStorage.end(),
		[](const auto& unit) {
			if (auto status = unit->getAspect<aspect::DeathStatus>())
			{
				return status->mIsDead;
			}
			return false;
		});

	if (auto logger = world.getEventLogger())
	{
		for (auto it = from; it != mStorage.end(); ++it)
		{
			logger->log(
				world.getSimulationStep(), sw::io::UnitDied { (*it)->getId() });
		}
	}

	mStorage.erase(from, mStorage.end());
}
