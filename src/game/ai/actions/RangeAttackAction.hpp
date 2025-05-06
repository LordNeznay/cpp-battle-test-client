#pragma once

#include "game/ai/ActionChainAI.hpp"

namespace ai::action
{
	class RangeAttack : public Action
	{
		bool exec(Unit& unit, GameWorld& world) override;
	};
}
