#pragma once

#include "Unit.hpp"

class GameWorld;

// Пул юнитов
class UnitPool
{
	using Storage = std::vector<std::unique_ptr<Unit>>;

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

	auto begin() { return mStorage.begin();	}
	auto begin() const { return mStorage.begin();	}
	auto end() { return mStorage.end();	}
	auto end() const { return mStorage.end();	}

protected:
	Storage mStorage;
};
