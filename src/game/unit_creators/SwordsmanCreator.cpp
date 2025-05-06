#include "SwordsmanCreator.hpp"
#include "game/base/GameWorld.hpp"
#include "game/base/Unit.hpp"
#include "game/base/UnitPool.hpp"
#include "game/base/Map.hpp"

#include "game/aspects/AIAspect.hpp"
#include "game/aspects/DeathStatusAspect.hpp"
#include "game/aspects/StrengthAspect.hpp"

#include "game/ai/ActionChainAI.hpp"
#include "game/ai/actions/MeleeAttackAction.hpp"
#include "game/ai/actions/MovementAction.hpp"

#include "IO/Commands/SpawnSwordsman.hpp"

void SwordsmanCreator::create(GameWorld& world, const sw::io::SpawnSwordsman& cmd)
{
	auto& unit = world.mUnitPool->spawnUnit(cmd.unitId);
	auto unitAI = std::make_unique<ai::ActionChainAI>();
	//unitAI->addAction() // TODO

	unit.addAspect(aspect::AI(std::move(unitAI)));
	unit.addAspect(aspect::DeathStatus{});
	unit.addAspect(aspect::Strength{(int)cmd.strength});

	world.mMap->addUnit(unit, Vec2{(int)cmd.x, (int)cmd.y});
}
