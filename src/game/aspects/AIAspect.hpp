#pragma once

#include "game/base/AspectStorage.hpp"

class GameWorld;
class Unit;

/// <summary>
/// ��������� �������� ��, ��������������� � aspect::AI
/// </summary>
class BaseAI
{
public:
	virtual ~BaseAI() = default;

	/// <summary>
	/// ��������� ������ �� ��� �����
	/// </summary>
	/// <param name="world"></param>
	virtual void Think(Unit& unit, GameWorld& world) = 0;
};

namespace aspect
{
	/// <summary>
	/// ������ �� �����
	/// </summary>
	class AI : public Aspect
	{
	public:
		AI(std::unique_ptr<BaseAI> impl) :
				mImpl(std::move(impl))
		{}

		/// <summary>
		/// ��������� ������ �� ��� �����
		/// </summary>
		/// <param name="unit">����, ��� �������� ����������� ������</param>
		/// <param name="world">������� ���</param>
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
