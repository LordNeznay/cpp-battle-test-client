#include "SwordsmanCreator.hpp"
#include "game/base/GameWorld.hpp"
#include "game/base/Unit.hpp"
#include "game/base/UnitPool.hpp"
#include "game/base/Map.hpp"

#include "game/aspects/AIAspect.hpp"
#include "game/aspects/DeathStatusAspect.hpp"
#include "game/aspects/StrengthAspect.hpp"
#include "game/aspects/HealthAspect.hpp"
#include "game/aspects/MeleeAttackRadiusAspect.hpp"

#include "game/ai/ActionChainAI.hpp"
#include "game/ai/actions/MeleeAttackAction.hpp"
#include "game/ai/actions/MovementAction.hpp"

#include "IO/System/EventLog.hpp"
#include "IO/Events/UnitSpawned.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"

void SwordsmanCreator::create(GameWorld& world, const sw::io::SpawnSwordsman& cmd)
{
	auto& unit = world.mUnitPool->spawnUnit(cmd.unitId);
	auto unitAI = std::make_unique<ai::ActionChainAI>();
	unitAI->addAction(std::make_unique<ai::action::MeleeAttack>());
	unitAI->addAction(std::make_unique<ai::action::Movement>());

	unit.addAspect(aspect::AI(std::move(unitAI)));
	unit.addAspect(aspect::DeathStatus{});
	unit.addAspect(aspect::Health{(int)cmd.hp});

	unit.addAspect(aspect::Strength{(int)cmd.strength});
	unit.addAspect(aspect::MeleeAttackRadius{ 0, 1 });

	world.mMap->addUnit(unit, Vec2{(int)cmd.x, (int)cmd.y});

	if (auto logger = world.getEventLogger())
	{
		logger->log(
			world.getSimulationStep(),
			sw::io::UnitSpawned{
				unit.getId(),
				"Swordsman",
				cmd.x,
				cmd.y
			});
	}
}
