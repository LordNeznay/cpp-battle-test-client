#include "RangeAttackAction.hpp"
#include "game/ai/DamageHelper.hpp"
#include "game/aspects/RangeAttackRadiusAspect.hpp"
#include "game/aspects/PositionAspect.hpp"
#include "game/aspects/AgilityAspect.hpp"
#include "game/base/GameWorld.hpp"
#include "game/base/RandomManager.hpp"
#include "game/base/Unit.hpp"

bool ai::action::RangeAttack::exec(Unit& unit, GameWorld& world)
{
	auto map = world.getGameMap();
	auto randomManager = world.getRandomManager();
	auto agility = unit.getAspect<aspect::Agility>();
	auto attackRadius = unit.getAspect<aspect::RangeAttackRadius>();

	if (not map || not randomManager || not agility || not attackRadius)
	{
		return false;
	}

	auto targets = DamageHelper::getUnitsInRadius(
		*map, unit, attackRadius->mMinValue, attackRadius->mMaxValue, DamageHelper::Filters::IsAttackable);

	if (targets.empty())
	{
		return false;
	}

	int idx = randomManager->random(targets.size());
	DamageHelper::applyDamage(world, unit, *targets[idx], agility->mValue);
	return true;
}

bool ai::action::RangeAttack::canAct(const Unit& unit, const GameWorld& world) const
{
	auto map = world.getGameMap();
	auto attackRadius = unit.getAspect<aspect::RangeAttackRadius>();

	if (not map || not attackRadius)
	{
		return false;
	}

	auto targets = DamageHelper::getUnitsInRadius(
		*map, unit, attackRadius->mMinValue, attackRadius->mMaxValue, DamageHelper::Filters::IsAttackable);
	return not targets.empty();
}

