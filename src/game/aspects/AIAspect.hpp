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
	BaseAI() = default;
	virtual ~BaseAI() = default;

	BaseAI(BaseAI&&) = default;
	BaseAI& operator=(BaseAI&&) = default;

	BaseAI(const BaseAI&) = delete;
	BaseAI& operator=(const BaseAI&) = delete;

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
		void Think(Unit& unit, GameWorld& world);

	protected:
		std::unique_ptr<BaseAI> mImpl;
	};
}
