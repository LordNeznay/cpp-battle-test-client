#pragma once

#include "game/ai/ActionChainAI.hpp"

namespace ai::action
{
	class Movement : public Action
	{
		bool exec(Unit& unit, GameWorld& world) override;
	};
}
