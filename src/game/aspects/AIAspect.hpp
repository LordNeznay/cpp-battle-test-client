#pragma once

#include "game/base/AspectStorage.hpp"

class GameWorld;
class Unit;

/// <summary>
/// Интерфейс базового ИИ, устанавливается в aspect::AI
/// </summary>
class BaseAI
{
public:
	virtual ~BaseAI() = default;

	/// <summary>
	/// Выполняем логику ИИ для юнита
	/// </summary>
	/// <param name="world"></param>
	virtual void Think(Unit& unit, GameWorld& world) = 0;
};

namespace aspect
{
	/// <summary>
	/// Аспект ИИ юнита
	/// </summary>
	class AI : public Aspect
	{
	public:
		AI(std::unique_ptr<BaseAI> impl) :
				mImpl(std::move(impl))
		{}

		/// <summary>
		/// Выполняем логику ИИ для юнита
		/// </summary>
		/// <param name="unit">Юнит, для которого выполняется логика</param>
		/// <param name="world">Игровой мир</param>
		void Think(Unit& unit, GameWorld& world)
		{
			if (mImpl)
			{
				mImpl->Think(unit, world);
			}
		}

	protected:
		std::unique_ptr<BaseAI> mImpl;
	};
}
