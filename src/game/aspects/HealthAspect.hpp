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
		/// <summary>
		/// Счетчик жизней
		/// </summary>
		bool mHealthPoints = 0;
	};
}
