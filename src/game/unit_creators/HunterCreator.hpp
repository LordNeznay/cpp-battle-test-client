#pragma once

class GameWorld;

namespace sw::io
{
	struct SpawnHunter;
}

class HunterCreator
{
public:
	static void create(GameWorld& world, const sw::io::SpawnHunter& cmd);
};
