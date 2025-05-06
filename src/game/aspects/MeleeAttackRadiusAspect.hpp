#pragma once

#include "game/base/AspectStorage.hpp"

namespace aspect
{
	/// <summary>
	/// Хранилище для показателя дальности физической атаки
	/// </summary>
	class MeleeAttackRadius : public Aspect
	{
	public:
		MeleeAttackRadius(int value) :
				mValue(value)
		{}

		/// <summary>
		/// Значение
		/// </summary>
		int mValue = 0;
	};
}
