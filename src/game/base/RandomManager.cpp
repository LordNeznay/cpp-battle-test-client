#include "RandomManager.hpp"

RandomManager::RandomManager(int seed) :
		mRandomGenerator(seed)
{
}

int RandomManager::random(int from, int to)
{
	std::uniform_int_distribution<> distr(from, to - 1);
	return distr(mRandomGenerator);
}
