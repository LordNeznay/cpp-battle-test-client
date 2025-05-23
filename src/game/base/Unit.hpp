#pragma once

#include "AspectStorage.hpp"

class GameWorld;

class Unit : public AspectStorage
{
	friend class UnitPool;

public:
	Unit() = default;
	Unit(Unit&&) = default;
	Unit& operator=(Unit&&) = default;

	Unit(const Unit&) = delete;
	Unit& operator=(const Unit&) = delete;

	/// <summary>
	/// Получить айдишник юнита
	/// </summary>
	/// <returns></returns>
	UnitId getId() const;

	/// <summary>
	/// Начать движение в указанную точку
	/// </summary>
	void marchStart(GameWorld& world, Vec2 targetPos);

	/// <summary>
	/// Является ли юнит живым
	/// </summary>
	/// <returns></returns>
	bool isAlive() const;

	/// <summary>
	/// Может ли юнит что-то делать в следующем ходу
	/// </summary>
	/// <returns></returns>
	bool canActOnNextStep(const GameWorld& world) const;

protected:
	UnitId mId = 0;
};
