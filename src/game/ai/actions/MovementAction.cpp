#include "MovementAction.hpp"
#include "game/base/Unit.hpp"
#include "game/base/GameWorld.hpp"
#include "game/base/Map.hpp"
#include "game/aspects/PositionAspect.hpp"
#include "game/aspects/MovementTargetAspect.hpp"

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

	map->moveUnit(unit, path[0]);
	if (targetPosition->mTargetPos == path[0])
	{
		unit.removeAspect<aspect::MovementTarget>();
	}

	return true;
}
