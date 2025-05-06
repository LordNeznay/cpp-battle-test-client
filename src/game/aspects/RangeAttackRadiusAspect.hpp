#pragma once

#include "game/base/AspectStorage.hpp"

namespace aspect
{
	/// <summary>
	/// Хранилище для показателя дальности стрелковой атаки
	/// </summary>
	class RandgeAttackRadius : public Aspect
	{
	public:
		RandgeAttackRadius(int value) :
				mValue(value)
		{}

		/// <summary>
		/// Значение
		/// </summary>
		int mValue = 0;
	};
}
