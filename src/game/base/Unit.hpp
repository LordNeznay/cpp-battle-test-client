#pragma once

#include "AspectStorage.hpp"

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
	void marchStart(Vec2 targetPos);

	/// <summary>
	/// Является ли юнит живым
	/// </summary>
	/// <returns></returns>
	bool isAlive() const;

protected:
	UnitId mId = 0;
};
