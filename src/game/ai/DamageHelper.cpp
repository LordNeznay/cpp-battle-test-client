#include "DamageHelper.hpp"
#include "game/base/Unit.hpp"
#include "game/base/Map.hpp"
#include "game/base/GameWorld.hpp"
#include "game/aspects/HealthAspect.hpp"
#include "game/aspects/DeathStatusAspect.hpp"

#include "IO/System/EventLog.hpp"
#include "IO/Events/UnitAttacked.hpp"

void DamageHelper::applyDamage(GameWorld& world, const Unit& unitFrom, Unit& unitTo, int value)
{
	if (auto health = unitTo.getAspect<aspect::Health>())
	{
		health->mHealthPoints -= value;

		if (health->mHealthPoints <= 0)
		{
			if (auto death = unitTo.getAspect<aspect::DeathStatus>())
			{
				death->mIsDead = true;
			}

			if (auto logger = world.getEventLogger())
			{
				logger->log(world.getSimulationStep(), sw::io::UnitAttacked{unitFrom.getId(), unitTo.getId(), (uint32_t)value, (uint32_t)std::max(0, health->mHealthPoints) });
			}
		}
	}
}

std::vector<Unit*> DamageHelper::getUnitsInRadius(Map& map, 
	const Vec2& pos, int radiusMin, int radiusMax, const std::function<bool(const Unit& unit)> filter)
{
	std::vector<Unit*> result;

	map.forEachCellInRadius(
		pos,
		radiusMin, radiusMax,
		[&filter, &result](const Vec2& pos, MapCell& cell) { 
			std::copy_if(
				cell.unitList.begin(),
				cell.unitList.end(),
				std::back_inserter(result),
				[&filter](Unit* ptr) { return filter(*ptr); });
		});

	return result;
}

bool DamageHelper::Filters::IsAlive(const Unit& unit) {
	return unit.isAlive();
}

bool DamageHelper::Filters::IsAttackable(const Unit& unit)
{
	return unit.getAspect<aspect::Health>() != nullptr && IsAlive(unit);
}
