#pragma once

#include "game/base/AspectStorage.hpp"

namespace aspect
{
	/// <summary>
	/// Хранилище для показателя дальности стрелковой атаки
	/// </summary>
	class RangeAttackRadius : public Aspect
	{
	public:
		RangeAttackRadius(int min, int max) :
				mMinValue(min),
				mMaxValue(max)
		{}

		/// <summary>
		/// Минимальный радиус
		/// </summary>
		int mMinValue = 0;

		/// <summary>
		/// Максимальный радиус
		/// </summary>
		int mMaxValue = 0;
	};
}
