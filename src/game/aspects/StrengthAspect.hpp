#pragma once

#include "game/base/AspectStorage.hpp"

namespace aspect
{
	/// <summary>
	/// Хранилище для показателя физической силы юнита
	/// </summary>
	class Strength : public Aspect
	{
	public:
		Strength(int value) :
				mValue(value)
		{}

		/// <summary>
		/// Сила юнита
		/// </summary>
		int mValue = 0;
	};
}
