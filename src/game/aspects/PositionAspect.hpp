#pragma once

#include "game/base/AspectStorage.hpp"

namespace aspect
{
	/// <summary>
	/// Позиция юнита в данный момент. Создается и управляется игровой картой
	/// </summary>
	class Position : public Aspect
	{
		friend class Map;

	public:
		Position(Position&&) = default;
		Position& operator=(Position&&) = default;

		Vec2 getPosition() const
		{
			return mPos;
		}

	protected:
		Position(const Vec2 pos) :
				mPos(pos)
		{}

	protected:
		Vec2 mPos;
	};
}
