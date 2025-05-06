#include "GameWorld.hpp"

#include "game/base/Map.hpp"
#include "game/base/UnitPool.hpp"
#include "game/unit_creators/SwordsmanCreator.hpp"
#include "game/aspects/HealthAspect.hpp"
#include "game/aspects/DeathStatusAspect.hpp"

#include "IO/System/EventLog.hpp"
#include "IO/Events/MapCreated.hpp"

#include "IO/Commands/March.hpp"
#include "IO/Commands/SpawnHunter.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"


GameWorld::GameWorld()
{
	mUnitPool = std::make_unique<UnitPool>();
}

GameWorld::~GameWorld() = default;

void GameWorld::setGameMap(std::unique_ptr<Map> map)
{
	if (not map)
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
	constexpr int sMaxSteps = 10; // TODO увеличить

	while (not isSimulationFinished() && mSimulationStep < sMaxSteps)
	{
		mSimulationStep += 1;
		step();

		printState(); // TODO: remove
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
	SwordsmanCreator::create(*this, cmd);
}

void GameWorld::spawnHunter(const sw::io::SpawnHunter& cmd)
{
	// TODO
}

void GameWorld::marchStart(const sw::io::March& cmd)
{
	// TODO
}

void GameWorld::printState()
{
	std::cout << std::format("Step: {}\n", mSimulationStep);
	std::cout << mMap->makeDebugView();

	for (auto& unit : *mUnitPool)
	{
		bool isDead = false;
		std::optional<int> hp;

		if (auto data = unit->getAspect<aspect::Health>())
		{
			hp = data->mHealthPoints;
		}

		if (auto data = unit->getAspect<aspect::DeathStatus>())
		{
			isDead = data->mIsDead;
		}

		std::cout << std::format("Unit {}. HP {}. IsDead {}", unit->getId(), hp.value_or(0), isDead) << std::endl;
	}

	std::cout << std::endl;
}
