#include "SwordsmanCreator.hpp"
#include "game/base/Unit.hpp"

#include "game/aspects/AIAspect.hpp"
#include "game/aspects/DeathStatusAspect.hpp"
#include "game/aspects/PositionAspect.hpp"
#include "game/aspects/MovementTargetAspect.hpp"

#include "game/ai/ActionChainAI.hpp"
#include "game/ai/actions/MeleeAttackAction.hpp"
#include "game/ai/actions/MovementAction.hpp"

#include "IO/Commands/SpawnSwordsman.hpp"

void SwordsmanCreator::create(Unit& unit, const sw::io::SpawnSwordsman& cmd)
{
	auto unitAI = std::make_unique<ai::ActionChainAI>();
	//unitAI->addAction() // TODO

	unit.addAspect(aspect::AI(std::move(unitAI)));
	unit.addAspect(aspect::DeathStatus{});
	unit.addAspect(aspect::Position{ (int)cmd.x, (int)cmd.y });
}
