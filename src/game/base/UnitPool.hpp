#pragma once

#include "Unit.hpp"

class GameWorld;

// ��� ������
class UnitPool
{
	using Storage = std::vector<std::unique_ptr<Unit>>;
	using Iterator = Storage::iterator;

public:
	/// <summary>
	/// ������� ����� � ����� ����������
	/// </summary>
	/// <param name="unitId"></param>
	Unit& spawnUnit(UnitId unitId);

	/// <summary>
	/// ������� ������� ������
	/// </summary>
	void removeDeathUnits(GameWorld& world);

protected:
	Storage mStorage;
};