#pragma once

#include "game/base/AspectStorage.hpp"

namespace aspect
{
	/// <summary>
	/// Точка, в которую движется юнит
	/// </summary>
	class MovementTarget : public Aspect
	{
	public:
		Vec2 mTargetPos;
	};
}
