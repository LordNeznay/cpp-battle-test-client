#include "GameWorld.hpp"

#include "game/base/Map.hpp"
#include "game/base/UnitPool.hpp"
#include "game/base/RandomManager.hpp"
#include "game/unit_creators/SwordsmanCreator.hpp"
#include "game/unit_creators/HunterCreator.hpp"
#include "game/aspects/HealthAspect.hpp"
#include "game/aspects/AIAspect.hpp"
#include "game/aspects/DeathStatusAspect.hpp"
#include "game/aspects/MovementTargetAspect.hpp"

#include "IO/System/EventLog.hpp"
#include "IO/Events/MapCreated.hpp"

#include "IO/Commands/March.hpp"
#include "IO/Commands/SpawnHunter.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"


GameWorld::GameWorld()
{
	mUnitPool = std::make_unique<UnitPool>();
	mRandomManager = std::make_unique<RandomManager>(0);
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

Map* GameWorld::getGameMap()
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
	mUnitPool->removeDeathUnits(*this);

	for (auto& [_, unit] : *mUnitPool)
	{
		if (auto unitAi = unit->getAspect<aspect::AI>())
		{
			unitAi->Think(*unit, *this);
		}
	}
}

void GameWorld::simulate()
{
	while (not isSimulationFinished() && mSimulationStep < sMaxSimulationSteps)
	{
		mSimulationStep += 1;
		step();

		printState();
	}
}

bool GameWorld::isSimulationFinished() const
{
	bool isHaveNoUnits = mUnitPool->getUnitCount() == 0;
	bool isAnyActionOnNextStep = std::any_of(
		mUnitPool->begin(),
		mUnitPool->end(),
		[this](const auto& pair) { 
			auto& unit = pair.second;
			return unit->canActOnNextStep(*this);
		});

	return isHaveNoUnits || not isAnyActionOnNextStep;
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
	HunterCreator::create(*this, cmd);
}

void GameWorld::marchStart(const sw::io::March& cmd)
{

	if (auto unit = mUnitPool->getUnit(cmd.unitId))
	{
		unit->marchStart(*this, Vec2{(int)cmd.targetX, (int)cmd.targetY});
	}
}

void GameWorld::printState()
{
	std::stringstream ss;
	ss << std::format("Step: {}\n", mSimulationStep);
	ss << mMap->makeDebugView();

	for (auto& [_, unit] : *mUnitPool)
	{
		ss << std::format("Unit {}.", unit->getId());

		if (auto data = unit->getAspect<aspect::Health>())
		{
			ss << std::format(" HP {}.", data->mHealthPoints);
		}

		if (auto data = unit->getAspect<aspect::DeathStatus>())
		{
			ss << std::format(" IsDead {}.", data->mIsDead);
		}

		if (auto data = unit->getAspect<aspect::MovementTarget>())
		{
			ss << std::format(" Move to {}x{}", data->mTargetPos.x, data->mTargetPos.y);
		}
		ss << std::endl;
	}

	if (sEnableDebugLogs)
	{
		std::cout << ss.str() << std::endl;
	}
}

RandomManager* GameWorld::getRandomManager()
{
	return mRandomManager.get();
}
