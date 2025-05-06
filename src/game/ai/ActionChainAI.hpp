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
		virtual ~Action() = default;

		/// <summary>
		/// Выполняем действие
		/// </summary>
		/// <param name="unit">Для этого юнита</param>
		/// <param name="world">В этом мире</param>
		/// <returns>Флаг успешности</returns>
		virtual bool exec(Unit& unit, GameWorld& world) = 0;
	};

	/// <summary>
	/// ИИ на основе цепочки действий, где выполняем все действия по цепочке до первого успешного
	/// </summary>
	class ActionChainAI : public BaseAI
	{
	public:
		ActionChainAI() = default;
		ActionChainAI(ActionChainAI&&) = default;
		ActionChainAI& operator=(ActionChainAI&&) = default;

		ActionChainAI(const ActionChainAI&) = delete;
		ActionChainAI& operator=(const ActionChainAI&) = delete;

		/// <summary>
		/// Добавляем действие в цепочку
		/// </summary>
		ActionChainAI& addAction(std::unique_ptr<Action> action) {
			mActions.emplace_back(std::move(action));
		}

		void Think(Unit& unit, GameWorld& world) override;

	protected:
		/// <summary>
		/// Список действий
		/// </summary>
		std::vector<std::unique_ptr<Action>> mActions;
	};
}
