#include "DamageHelper.hpp"
#include "game/base/Unit.hpp"
#include "game/base/Map.hpp"
#include "game/base/GameWorld.hpp"
#include "game/aspects/HealthAspect.hpp"
#include "game/aspects/DeathStatusAspect.hpp"
#include "game/aspects/PositionAspect.hpp"

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

std::vector<Unit*> DamageHelper::getUnitsInRadius(const Map& map, 
	const Vec2& pos, int radiusMin, int radiusMax, const std::function<bool(const Unit& unit)> filter)
{
	std::vector<Unit*> result;

	map.forEachCellInRadius(
		pos,
		radiusMin, radiusMax,
		[&filter, &result](const Vec2& pos, const MapCell& cell) { 
			std::copy_if(
				cell.unitList.begin(),
				cell.unitList.end(),
				std::back_inserter(result),
				[&filter](Unit* ptr) { return filter(*ptr); });
		});

	return result;
}

std::vector<Unit*> DamageHelper::getUnitsInRadius(
	const Map& map,
	const Unit& actor,
	int radiusMin,
	int radiusMax,
	const std::function<bool(const Unit& unit)> filter,
	bool excludeActor)
{
	auto position = actor.getAspect<aspect::Position>();
	if (not position)
	{
		return {};
	}

	auto targets = DamageHelper::getUnitsInRadius(
		map,
		position->getPosition(), radiusMin, radiusMax,
		DamageHelper::Filters::IsAttackable);
	if (excludeActor)
	{
		targets.erase(
			std::remove_if(targets.begin(), targets.end(), [&actor](const auto& u) { return &actor == u; }),
			targets.end());
	}

	return targets;
}

bool DamageHelper::Filters::IsAlive(const Unit& unit) {
	return unit.isAlive();
}

bool DamageHelper::Filters::IsAttackable(const Unit& unit)
{
	return unit.getAspect<aspect::Health>() != nullptr && IsAlive(unit);
}
