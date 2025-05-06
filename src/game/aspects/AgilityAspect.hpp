#pragma once

#include "game/base/AspectStorage.hpp"

namespace aspect
{
	/// <summary>
	/// Хранилище для показателя ловкости юнита
	/// </summary>
	class Agility : public Aspect
	{
	public:
		Agility(int value) :
				mValue(value)
		{}

		/// <summary>
		/// Ловкость юнита
		/// </summary>
		int mValue = 0;
	};
}
