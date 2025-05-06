#pragma once

class GameWorld;

namespace sw::io
{
	struct SpawnSwordsman;
}

class SwordsmanCreator
{
public:
	static void create(GameWorld& world, const sw::io::SpawnSwordsman& cmd);
};
