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
	/// ������������� ������� �����
	/// </summary>
	/// <param name="map"></param>
	void setGameMap(std::unique_ptr<Map> map);

	/// <summary>
	/// �������� ������� �����, ���� ��� ����
	/// </summary>
	const Map* getGameMap() const;

	/// <summary>
	/// ������������� ������ ������� �������
	/// </summary>
	/// <param name="logger"></param>
	void setEventLogger(std::unique_ptr<sw::EventLog> logger);

	/// <summary>
	/// �������� ������ ��� ������� �������
	/// </summary>
	sw::EventLog* getEventLogger();

	/// <summary>
	/// ��������� ��� ��������� �������� ����
	/// </summary>
	void step();

	/// <summary>
	/// ������������ ������� ��� �� �����
	/// </summary>
	void simulate();

	/// <summary>
	/// ��������� ��������� ��� ���
	/// </summary>
	/// <returns></returns>
	bool isSimulationFinished() const;

	/// <summary>
	/// �������� ����� ���� ���������
	/// </summary>
	/// <returns></returns>
	int getSimulationStep() const;

	/// <summary>
	/// ������� �������
	/// </summary>
	/// <param name="cmd">������� � ����������� ��� ������</param>
	void spawnSwordsman(const sw::io::SpawnSwordsman& cmd);

	/// <summary>
	/// ������� ��������
	/// </summary>
	/// <param name="cmd">������� � ����������� ��� ������</param>
	void spawnHunter(const sw::io::SpawnHunter& cmd);

	/// <summary>
	/// ��������� ����������� �����
	/// </summary>
	/// <param name="cmd">��������� �����������</param>
	void marchStart(const sw::io::March& cmd);

protected:
	/// <summary>
	/// ����� �������� ����
	/// </summary>
	std::unique_ptr<Map> mMap;
	/// <summary>
	/// ��� ������
	/// </summary>
	std::unique_ptr<UnitPool> mUnitPool;
	/// <summary>
	/// ������ ��� ������� �������
	/// </summary>
	std::unique_ptr<sw::EventLog> mLogger;
	/// <summary>
	/// ����� ���� ���������
	/// </summary>
	int mSimulationStep = 0;
};
