#pragma once

#include "game/aspects/AIAspect.hpp"

namespace ai
{
	/// <summary>
	/// �����-�� �������� ��
	/// </summary>
	class Action
	{
	public:
		virtual ~Action() = default;

		/// <summary>
		/// ��������� ��������
		/// </summary>
		/// <param name="unit">��� ����� �����</param>
		/// <param name="world">� ���� ����</param>
		/// <returns>���� ����������</returns>
		virtual bool exec(Unit& unit, GameWorld& world) = 0;
	};

	/// <summary>
	/// �� �� ������ ������� ��������, ��� ��������� ��� �������� �� ������� �� ������� ���������
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
		/// ��������� �������� � �������
		/// </summary>
		ActionChainAI& addAction(std::unique_ptr<Action> action) {
			mActions.emplace_back(std::move(action));
		}

		void Think(Unit& unit, GameWorld& world) override;

	protected:
		/// <summary>
		/// ������ ��������
		/// </summary>
		std::vector<std::unique_ptr<Action>> mActions;
	};
}
