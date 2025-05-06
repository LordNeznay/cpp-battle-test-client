#include "MovementAction.hpp"
#include "game/base/Unit.hpp"
#include "game/base/GameWorld.hpp"
#include "game/base/Map.hpp"
#include "game/aspects/PositionAspect.hpp"
#include "game/aspects/MovementTargetAspect.hpp"

#include "IO/System/EventLog.hpp"
#include "IO/Events/MarchEnded.hpp"

bool ai::action::Movement::exec(Unit& unit, GameWorld& world)
{
	auto map = world.getGameMap();
	auto position = unit.getAspect<aspect::Position>();
	auto targetPosition = unit.getAspect<aspect::MovementTarget>();

	if (not map || not position || not targetPosition)
	{
		return false;
	}

	auto path = map->findPath(
		position->getPosition(), targetPosition->mTargetPos, [](const auto& cell) { return cell.unitList.empty();
		});
	if (path.empty())
	{
		return false;
	}

	auto currentPos = path[0];
	map->moveUnit(unit, currentPos);
	if (targetPosition->mTargetPos == currentPos)
	{
		unit.removeAspect<aspect::MovementTarget>();

		if (auto logger = world.getEventLogger())
		{
			logger->log(
				world.getSimulationStep(),
				sw::io::MarchEnded{
					unit.getId(),
					(uint32_t)currentPos.x, (uint32_t)currentPos.y});
		}
	}

	return true;
}

bool ai::action::Movement::canAct(const Unit& unit, const GameWorld& world) const {
	return unit.getAspect<aspect::MovementTarget>() != nullptr;
}
