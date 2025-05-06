#include "MeleeAttackAction.hpp"
#include "game/base/Unit.hpp"
#include "game/base/GameWorld.hpp"
#include "game/base/RandomManager.hpp"
#include "game/ai/DamageHelper.hpp"
#include "game/aspects/PositionAspect.hpp"
#include "game/aspects/StrengthAspect.hpp"
#include "game/aspects/MeleeAttackRadiusAspect.hpp"

bool ai::action::MeleeAttack::exec(Unit& unit, GameWorld& world)
{
	auto map = world.getGameMap();
	auto randomManager = world.getRandomManager();
	auto strength = unit.getAspect<aspect::Strength>();
	auto attackRadius = unit.getAspect<aspect::MeleeAttackRadius>();

	if (not map || not randomManager || not strength || not attackRadius)
	{
		return false;
	}

	auto targets = DamageHelper::getUnitsInRadius(
		*map, unit,
		attackRadius->mMinValue,
		attackRadius->mMaxValue,
		DamageHelper::Filters::IsAttackable);

	if (targets.empty())
	{
		return false;
	}

	int idx = randomManager->random(targets.size());
	DamageHelper::applyDamage(world, unit, *targets[idx], strength->mValue);
	return true;
}

bool ai::action::MeleeAttack::canAct(const Unit& unit, const GameWorld& world) const
{
	auto map = world.getGameMap();
	auto attackRadius = unit.getAspect<aspect::MeleeAttackRadius>();

	if (not map || not attackRadius)
	{
		return false;
	}

	auto targets = DamageHelper::getUnitsInRadius(
		*map, unit, attackRadius->mMinValue, attackRadius->mMaxValue, DamageHelper::Filters::IsAttackable);
	return not targets.empty();
}
