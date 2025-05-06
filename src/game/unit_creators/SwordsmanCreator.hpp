#pragma once

class Unit;
namespace sw::io
{
	class SpawnSwordsman;
}

class SwordsmanCreator
{
public:
	static void create(Unit& unit, const sw::io::SpawnSwordsman& cmd);
};