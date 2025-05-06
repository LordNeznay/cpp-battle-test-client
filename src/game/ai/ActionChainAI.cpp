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
