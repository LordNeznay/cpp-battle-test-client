#include "GameWorld.hpp"

#include "game/base/Map.hpp"
#include "game/base/UnitPool.hpp"
#include "game/unit_creators/SwordsmanCreator.hpp"

#include "IO/System/EventLog.hpp"
#include "IO/Events/MapCreated.hpp"

#include "IO/Commands/March.hpp"
#include "IO/Commands/SpawnHunter.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"


GameWorld::GameWorld() = default;
GameWorld::~GameWorld() = default;

void GameWorld::setGameMap(std::unique_ptr<Map> map)
{
	if (not mMap)
	{
		throw std::runtime_error("New map is null");
	}

	if (mMap)
	{
		throw std::runtime_error("Map already set");
	}

	mMap = std::move(map);

	if (mLogger)
	{
		mLogger->log(mSimulationStep, sw::io::MapCreated{(uint32_t)mMap->getWidth(), (uint32_t)mMap->getHeight()});
	}
}

const Map* GameWorld::getGameMap() const
{
	return mMap.get();
}

void GameWorld::setEventLogger(std::unique_ptr<sw::EventLog> logger) 
{
	mLogger = std::move(logger);
}

sw::EventLog* GameWorld::getEventLogger() 
{
	return mLogger.get();
}

void GameWorld::step() 
{
	// TODO
}

void GameWorld::simulate()
{
	while (not isSimulationFinished())
	{
		mSimulationStep += 1;
		step();
	}
}

bool GameWorld::isSimulationFinished() const
{
	return false; // TODO
}

int GameWorld::getSimulationStep() const 
{
	return mSimulationStep;
}

void GameWorld::spawnSwordsman(const sw::io::SpawnSwordsman& cmd)
{
	auto& unit = mUnitPool->spawnUnit(cmd.unitId);

}

void GameWorld::spawnHunter(const sw::io::SpawnHunter& cmd)
{
	// TODO
}

void GameWorld::marchStart(const sw::io::March& cmd)
{
	// TODO
}
