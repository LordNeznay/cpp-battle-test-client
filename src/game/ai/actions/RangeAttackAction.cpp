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
	auto position = unit.getAspect<aspect::Position>();
	auto agility = unit.getAspect<aspect::Agility>();
	auto attackRadius = unit.getAspect<aspect::RangeAttackRadius>();

	if (not map || not randomManager || not position || not agility || not attackRadius)
	{
		return false;
	}

	auto targets = DamageHelper::getUnitsInRadius(
		*map, position->getPosition(), attackRadius->mMinValue, attackRadius->mMaxValue, DamageHelper::Filters::IsAttackable);
	targets.erase(
		std::remove_if(targets.begin(), targets.end(), [&unit](const auto& u) { return &unit == u; }), targets.end());

	if (targets.empty())
	{
		return false;
	}

	int idx = randomManager->random(targets.size());
	DamageHelper::applyDamageTo(*targets[idx], agility->mValue);
	return true;
}
