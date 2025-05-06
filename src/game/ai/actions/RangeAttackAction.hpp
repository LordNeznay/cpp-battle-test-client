#pragma once

#include "game/ai/ActionChainAI.hpp"

namespace ai::action
{
	class RangeAttack : public Action
	{
		bool exec(Unit& unit, GameWorld& world) override;
		bool canAct(const Unit& unit, const GameWorld& world) const override;
	};
}
