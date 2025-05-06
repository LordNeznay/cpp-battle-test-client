#pragma once

#include "game/base/AspectStorage.hpp"

namespace aspect
{
	/// <summary>
	/// ������� ����� � ������ ������
	/// </summary>
	class Position : public Aspect
	{
	public:
		Position(int x, int y) :
				mX(x),
				mY(y)
		{}

		int mX = 0;
		int mY = 0;
	};
}
