#pragma once
#include <random>

class RandomManager
{
public:
	RandomManager(int seed);
	virtual ~RandomManager() = default;

	RandomManager(RandomManager&&) = default;
	RandomManager& operator=(RandomManager&&) = default;

	RandomManager(const RandomManager&) = delete;
	RandomManager& operator=(const RandomManager&) = delete;

	/// <summary>
	/// Генерим случайное значение [from, to)
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <returns></returns>
	int random(int from, int to);
	int random(int to) { return random(0, to); }

protected:
	std::mt19937 mRandomGenerator;
};
