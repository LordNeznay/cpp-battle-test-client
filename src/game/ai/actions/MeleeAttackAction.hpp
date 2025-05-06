#pragma once

#include "game/ai/ActionChainAI.hpp"

namespace ai::action
{
	class MeleeAttack : public Action
	{
		bool exec(Unit& unit, GameWorld& world) override;
	};
}
