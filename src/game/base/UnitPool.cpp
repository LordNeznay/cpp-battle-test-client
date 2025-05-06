#include "UnitPool.hpp"

#include "game/base/GameWorld.hpp"
#include "game/base/Map.hpp"
#include "game/aspects/DeathStatusAspect.hpp"

#include "IO/System/EventLog.hpp"
#include "IO/Events/UnitDied.hpp"

Unit& UnitPool::spawnUnit(UnitId unitId)
{
	auto it = mStorage.emplace(unitId, std::make_unique<Unit>()).first;

	auto& unit = *it->second;
	unit.mId = unitId;

	return unit;
}

void UnitPool::removeDeathUnits(GameWorld& world)
{
	const auto isNeedToRemove = [](const Unit& unit) {
		if (auto status = unit.getAspect<aspect::DeathStatus>())
		{
			return status->mIsDead;
		}
		return false;
	};

	for (auto it = mStorage.begin(); it != mStorage.end();)
	{
		if (isNeedToRemove(*it->second))
		{
			beforeUnitErase(world, *it->second);
			it = mStorage.erase(it);
		}
		else
		{
			it = std::next(it);
		}
	}
}

void UnitPool::beforeUnitErase(GameWorld& world, Unit& unit) {
	if (auto logger = world.getEventLogger())
	{
		logger->log(world.getSimulationStep(), sw::io::UnitDied{unit.getId()});
	}

	if (auto map = world.getGameMap())
	{
		map->removeUnit(unit);
	}
}

Unit* UnitPool::getUnit(UnitId unitId) 
{
	if (auto it = mStorage.find(unitId); it != mStorage.end())
	{
		return it->second.get();
	}

	return nullptr;
}

const Unit* UnitPool::getUnit(UnitId unitId) const
{
	if (auto it = mStorage.find(unitId); it != mStorage.end())
	{
		return it->second.get();
	}

	return nullptr;
}

int UnitPool::getUnitCount() const
{
	return mStorage.size();
}
