#pragma once

class Unit;
class GameWorld;

class MapCell
{
public:
	std::list<Unit*> unitList;
};

class Map
{
public:
	static const std::vector<Vec2> sDefaultWalkDirections;

public:
	Map(int w, int h);

	/// <summary>
	/// Устанавливаем мир-владельца карты
	/// </summary>
	void setGameWorld(GameWorld& world);

	/// <summary>
	/// Получить ширину карты
	/// </summary>
	/// <returns></returns>
	int getWidth() const;
	
	/// <summary>
	/// Получить высоту карты
	/// </summary>
	/// <returns></returns>
	int getHeight() const;

	/// <summary>
	/// Построить путь. Стартовую точку считаем автоматически проходимой
	/// </summary>
	/// <param name="from">Откуда строим</param>
	/// <param name="to">Куда строим</param>
	/// <param name="isCellFreeCb">Предикат для определения свободности клетки</param>
	/// <returns>Построенный путь без учета стартовой точки. Если нельзя построить, то пустой массив</returns>
	std::vector<Vec2> findPath(const Vec2& from, const Vec2& to, const std::function<bool(const MapCell&)>& isCellFreeCb) const;

	/// <summary>
	/// Валидная ли эта позиция
	/// </summary>
	bool isValidPos(const Vec2& pos) const;

	/// <summary>
	/// Добавляем юнита на карту в указанную позицию
	/// </summary>
	void addUnit(Unit& unit, const Vec2& pos);

	/// <summary>
	/// Удаляем юнита с карты
	/// </summary>
	void removeUnit(Unit& unit);

	/// <summary>
	/// Двигаем юнита в указанную позицию
	/// </summary>
	void moveUnit(Unit& unit, const Vec2 pos);

	/// <summary>
	/// Дебажная визуализация
	/// </summary>
	/// <returns></returns>
	std::string makeDebugView() const;

	/// <summary>
	/// Обходим клетки начиная с указанной. Обходим по кругам начиная с наименьшего, пока не достигнем указанного радиуса
	/// </summary>
	/// <param name="center">Точка, от которой идет обход</param>
	/// <param name="radiusMin">Минимальный радиус (включительно)</param>
	/// <param name="radiusMax">Максимальный радиус (включительно)</param>
	/// <param name="visitCb">Коллбек для каждой клетки</param>
	using forEachCellInRadiusCb = const std::function<void(const Vec2&/* pos */, MapCell& /* cell */)>;
	void forEachCellInRadius(const Vec2& center, int radiusMin, int radiusMax, forEachCellInRadiusCb& visitCb);

protected:
	/// <summary>
	/// Ищем клетку по позиции
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	MapCell* getCell(const Vec2& pos);
	const MapCell* getCell(const Vec2& pos) const;

	/// <summary>
	/// Конвертируем позицию во внутренний индекс
	/// </summary>
	int posToIdx(const Vec2& pos) const;

	/// <summary>
	/// Конвертируем внутренний индекс в позицию
	/// </summary>
	Vec2 idxToPos(int idx) const;

protected:
	// Ширина карты
	int mWidth = 0;
	// Высота карты
	int mHeight = 0;
	/// <summary>
	/// Клетки карты
	/// </summary>
	std::vector<MapCell> mMapCells;
	/// <summary>
	/// Кеш поиска позиции по юниту
	/// </summary>
	std::unordered_map<Unit*, Vec2> mUnitToPosition;
	/// <summary>
	/// Владелец карты
	/// </summary>
	GameWorld* mWorld = nullptr;
};
