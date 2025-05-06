#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>
#include <fstream>
#include <iostream>

#include "game/base/GameWorld.hpp"
#include "game/base/Map.hpp"

/// <summary>
/// Создаем игровой мир по конфигу
/// </summary>
/// <param name="filepath">Путь к файлу команд конфига</param>
/// <returns>Игровой мир</returns>
std::unique_ptr<GameWorld> createWorldFromConfig(const std::string& filepath)
{
	std::ifstream file(filepath);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + filepath);
	}

	auto world = std::make_unique<GameWorld>();
	world->setEventLogger(std::make_unique<sw::EventLog>());

	sw::io::CommandParser parser;
	
	parser.add<sw::io::CreateMap>([&world](auto command) { 
		sw::printDebug(std::cout, command); 
		if (world->getGameMap())
		{
			throw std::runtime_error("Map already exist");
		}
		world->setGameMap(std::make_unique<Map>(command.width, command.height));
	});
	parser.add<sw::io::SpawnSwordsman>([&world](auto command) { 
		sw::printDebug(std::cout, command); 
		world->spawnSwordsman(command);
	});
	//parser.add<sw::io::SpawnHunter>([&world](auto command) { 
	//	sw::printDebug(std::cout, command); 
	//	world->spawnHunter(command);
	//});
	//parser.add<sw::io::March>([&world](auto command) { 
	//	sw::printDebug(std::cout, command); 
	//	world->marchStart(command);
	//});

	std::cout << "Commands:\n";
	parser.parse(file);

	return world;
}

int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	auto world = createWorldFromConfig(argv[1]);
	if (not world)
	{
		throw std::runtime_error("Error: Game world was not created");
	}

	//std::cout << "\n\nEvents:\n";

	//EventLog eventLog;

	//eventLog.log(1, io::MapCreated{10, 10});
	//eventLog.log(1, io::UnitSpawned{1, "Swordsman", 0, 0});
	//eventLog.log(1, io::UnitSpawned{2, "Hunter", 9, 0});
	//eventLog.log(1, io::MarchStarted{1, 0, 0, 9, 0});
	//eventLog.log(1, io::MarchStarted{2, 9, 0, 0, 0});
	//eventLog.log(1, io::UnitSpawned{3, "Swordsman", 0, 9});
	//eventLog.log(1, io::MarchStarted{3, 0, 9, 0, 0});

	//eventLog.log(2, io::UnitMoved{1, 1, 0});
	//eventLog.log(2, io::UnitMoved{2, 8, 0});
	//eventLog.log(2, io::UnitMoved{3, 0, 8});

	//eventLog.log(3, io::UnitMoved{1, 2, 0});
	//eventLog.log(3, io::UnitMoved{2, 7, 0});
	//eventLog.log(3, io::UnitMoved{3, 0, 7});

	//eventLog.log(4, io::UnitMoved{1, 3, 0});
	//eventLog.log(4, io::UnitAttacked{2, 1, 5, 0});
	//eventLog.log(4, io::UnitDied{1});
	//eventLog.log(4, io::UnitMoved{3, 0, 6});

	//eventLog.log(5, io::UnitMoved{2, 6, 0});
	//eventLog.log(5, io::UnitMoved{3, 0, 5});

	//eventLog.log(6, io::UnitMoved{2, 5, 0});
	//eventLog.log(6, io::UnitMoved{3, 0, 4});

	//eventLog.log(7, io::UnitAttacked{2, 3, 5, 5});
	//eventLog.log(7, io::UnitMoved{3, 0, 3});

	//eventLog.log(8, io::UnitAttacked{2, 3, 5, 0});
	//eventLog.log(8, io::UnitDied{3});

	return 0;
}
