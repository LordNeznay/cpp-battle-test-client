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
		MovementTarget(int x, int y) :
				mX(x),
				mY(y)
		{}

		int mX = 0;
		int mY = 0;
	};
}
