#pragma once

#include "game/base/AspectStorage.hpp"

namespace aspect
{
	/// <summary>
	/// Хранилище для счетчика жизней
	/// </summary>
	class Health : public Aspect
	{
	public:
		Health(int value) :
			mHealthPoints(value)
		{}

		/// <summary>
		/// Счетчик жизней
		/// </summary>
		int mHealthPoints = 0;
	};
}
