#pragma once

#include "game/base/AspectStorage.hpp"

namespace aspect
{
	/// <summary>
	/// ��������� ��� ������� ������
	/// </summary>
	class DeathStatus : public Aspect
	{
	public:
		/// <summary>
		/// ���� ���� ��� ���
		/// </summary>
		bool mIsDead = false;
	};
}
