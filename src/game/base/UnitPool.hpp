#pragma once

#include "Unit.hpp"

class GameWorld;

// Пул юнитов
class UnitPool
{
	using Storage = std::vector<std::unique_ptr<Unit>>;
	using Iterator = Storage::iterator;

public:
	/// <summary>
	/// Спавним юнита с таким айдишников
	/// </summary>
	/// <param name="unitId"></param>
	Unit& spawnUnit(UnitId unitId);

	/// <summary>
	/// Удаляем мертвых юнитов
	/// </summary>
	void removeDeathUnits(GameWorld& world);

protected:
	Storage mStorage;
};
