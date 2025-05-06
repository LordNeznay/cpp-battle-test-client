#pragma once

#include "game/base/AspectStorage.hpp"

namespace aspect
{
	/// <summary>
	/// Хранилище для маркера смерти
	/// </summary>
	class DeathStatus : public Aspect
	{
	public:
		/// <summary>
		/// Мерт юнит или нет
		/// </summary>
		bool mIsDead = false;
	};
}
