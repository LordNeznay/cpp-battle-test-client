#include "DamageHelper.hpp"
#include "game/base/Unit.hpp"
#include "game/base/Map.hpp"
#include "game/aspects/HealthAspect.hpp"
#include "game/aspects/DeathStatusAspect.hpp"

void DamageHelper::applyDamageTo(Unit& unit, int value)
{
	if (auto health = unit.getAspect<aspect::Health>())
	{
		health->mHealthPoints -= value;

		if (health->mHealthPoints <= 0)
		{
			if (auto death = unit.getAspect<aspect::DeathStatus>())
			{
				death->mIsDead = true;
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
