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
	auto position = unit.getAspect<aspect::Position>();
	auto strength = unit.getAspect<aspect::Strength>();
	auto attackRadius = unit.getAspect<aspect::MeleeAttackRadius>();

	if (not map || not randomManager || not position || not strength || not attackRadius)
	{
		return false;
	}

	auto targets = DamageHelper::getUnitsInRadius(
		*map, position->getPosition(), attackRadius->mValue, DamageHelper::Filters::IsAttackable);
	targets.erase(
		std::remove_if(targets.begin(), targets.end(), [&unit](const auto& u) { return &unit == u; }), targets.end());

	if (targets.empty())
	{
		return false;
	}

	int idx = randomManager->random(targets.size());
	DamageHelper::applyDamageTo(*targets[idx], strength->mValue);
	return true;
}
