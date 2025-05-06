#pragma once

class Map;
class UnitPool;

namespace sw
{
	class EventLog;
}
namespace sw::io {
	struct SpawnSwordsman;
	struct SpawnHunter;
	struct March;
}

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	/// <summary>
	/// Устанавливаем игровую карту
	/// </summary>
	/// <param name="map"></param>
	void setGameMap(std::unique_ptr<Map> map);

	/// <summary>
	/// Получить игровую карту, если она есть
	/// </summary>
	const Map* getGameMap() const;

	/// <summary>
	/// Устанавливаем логгер игровых событий
	/// </summary>
	/// <param name="logger"></param>
	void setEventLogger(std::unique_ptr<sw::EventLog> logger);

	/// <summary>
	/// Получить логгер для игровых событий
	/// </summary>
	sw::EventLog* getEventLogger();

	/// <summary>
	/// Выполнить шаг симуляции игрового мира
	/// </summary>
	void step();

	/// <summary>
	/// Симулировать игровой мир до конца
	/// </summary>
	void simulate();

	/// <summary>
	/// Завершена симуляция или нет
	/// </summary>
	/// <returns></returns>
	bool isSimulationFinished() const;

	/// <summary>
	/// Получить номер шага симуляции
	/// </summary>
	/// <returns></returns>
	int getSimulationStep() const;

	/// <summary>
	/// Спавним мечника
	/// </summary>
	/// <param name="cmd">Команда с настройками для спавна</param>
	void spawnSwordsman(const sw::io::SpawnSwordsman& cmd);

	/// <summary>
	/// Спавним охотника
	/// </summary>
	/// <param name="cmd">Команда с настройками для спавна</param>
	void spawnHunter(const sw::io::SpawnHunter& cmd);

	/// <summary>
	/// Планируем перемещение юнита
	/// </summary>
	/// <param name="cmd">Настройки перемещения</param>
	void marchStart(const sw::io::March& cmd);

protected:
	/// <summary>
	/// Карта игрового мира
	/// </summary>
	std::unique_ptr<Map> mMap;
	/// <summary>
	/// Пул юнитов
	/// </summary>
	std::unique_ptr<UnitPool> mUnitPool;
	/// <summary>
	/// Логгер для игровых событий
	/// </summary>
	std::unique_ptr<sw::EventLog> mLogger;
	/// <summary>
	/// Номер шага симуляции
	/// </summary>
	int mSimulationStep = 0;
};

