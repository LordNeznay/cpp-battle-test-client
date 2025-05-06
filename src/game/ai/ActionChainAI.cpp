#include "ActionChainAI.hpp"

void ai::ActionChainAI::Think(Unit& unit, GameWorld& world)
{
	for (auto& action : mActions)
	{
		if (action->exec(unit, world))
		{
			return;
		}
	}
}

bool ai::ActionChainAI::canAct(const Unit& unit, const GameWorld& world) const
{
	for (auto& action : mActions)
	{
		if (action->canAct(unit, world))
		{
			return true;
		}
	}

	return false;
}
