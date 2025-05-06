#pragma once

class Unit;
class Map;

class DamageHelper
{
public:
	/// <summary>
	/// Применяем указанный урон на юнита
	/// </summary>
	/// <param name="unit"></param>
	/// <param name="value"></param>
	static void applyDamageTo(Unit& unit, int value);

	/// <summary>
	/// Собрать список юнитов в определенном радиусе от указанной точки, которые удовлетворяют условию
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="filter"></param>
	/// <returns></returns>
	static std::vector<Unit*> getUnitsInRadius(Map& map, const Vec2& pos, int radius, const std::function<bool(const Unit& unit)> filter);

	/// <summary>
	/// Вспомогательные фильтры юнитов
	/// </summary>
	class Filters
	{
	public:
		/// <summary>
		/// Фильтр живых юнитов
		/// </summary>
		/// <param name="unit"></param>
		/// <returns></returns>
		static bool IsAlive(const Unit& unit);
		
		/// <summary>
		/// Фильтр юнитов, которых можно атаковать
		/// </summary>
		/// <param name="unit"></param>
		/// <returns></returns>
		static bool IsAttackable(const Unit& unit);
	};
};
