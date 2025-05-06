#pragma once

#include "game/aspects/AIAspect.hpp"

namespace ai
{
	/// <summary>
	/// Какое-то действие ИИ
	/// </summary>
	class Action
	{
	public:
		Action() = default;
		virtual ~Action() = default;

		Action(Action&&) = default;
		Action& operator=(Action&&) = default;

		Action(const Action&) = delete;
		Action& operator=(const Action&) = delete;

		/// <summary>
		/// Выполняем действие
		/// </summary>
		/// <param name="unit">Для этого юнита</param>
		/// <param name="world">В этом мире</param>
		/// <returns>Флаг успешности</returns>
		virtual bool exec(Unit& unit, GameWorld& world) = 0;

		/// <summary>
		/// Может ли юнит действовать в текущей ситуации
		/// </summary>
		virtual bool canAct(const Unit& unit, const GameWorld& world) const = 0;
	};

	/// <summary>
	/// ИИ на основе цепочки действий, где выполняем все действия по цепочке до первого успешного
	/// </summary>
	class ActionChainAI : public BaseAI
	{
	public:
		ActionChainAI() = default;

		/// <summary>
		/// Добавляем действие в цепочку
		/// </summary>
		ActionChainAI& addAction(std::unique_ptr<Action> action) {
			mActions.emplace_back(std::move(action));
			return *this;
		}

		void Think(Unit& unit, GameWorld& world) override;
		bool canAct(const Unit& unit, const GameWorld& world) const override;

	protected:
		/// <summary>
		/// Список действий
		/// </summary>
		std::vector<std::unique_ptr<Action>> mActions;
	};
}
