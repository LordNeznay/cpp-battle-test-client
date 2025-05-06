#include "Map.hpp"
#include "game/base/Unit.hpp"
#include <stack>

Map::Map(int w, int h) :
	mWidth(w),
	mHeight(h)
{
	mMapCells.resize(posToIdx(Vec2{mWidth - 1, mHeight - 1}));
}

int Map::getWidth() const
{
	return mWidth;
}

int Map::getHeight() const
{
	return mHeight;
}

std::vector<Vec2> Map::findPath(
	const Vec2& from, const Vec2& to, const std::function<bool(const MapCell&)>& isCellFreeCb) const
{
	std::vector<Vec2> path;

	if (!isValidPos(from) || !isValidPos(to))
	{
		return path;
	}

	std::stack<Vec2> stack;
	std::unordered_map<int, int> cameFrom;
	std::vector<bool> visited(mWidth * mHeight, false);

	stack.push(from);
	visited[posToIdx(from)] = true;

	// По часовой стрелке с LT. В будущем стоит вынести в параметры для возможности использовать более сложное движение
	std::vector<Vec2> directions = {{-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}};

	while (!stack.empty())
	{
		Vec2 current = stack.top();
		stack.pop();

		if (current.x == to.x && current.y == to.y)
		{
			break;
		}

		for (const Vec2& dir : directions)
		{
			Vec2 next = {current.x + dir.x, current.y + dir.y};
			if (!isValidPos(next))
			{
				continue;
			}

			int nextIdx = posToIdx(next);
			if (visited[nextIdx])
			{
				continue;
			}

			if (nextIdx != posToIdx(to) && !isCellFreeCb(mMapCells[nextIdx]))
			{
				continue;
			}

			stack.push(next);
			visited[nextIdx] = true;
			cameFrom[nextIdx] = posToIdx(current);
		}
	}

	// Восстановление пути
	int goalIdx = posToIdx(to);
	int startIdx = posToIdx(from);
	if (!cameFrom.contains(goalIdx))
	{
		return path;
	}

	for (int at = goalIdx; at != startIdx; at = cameFrom[at])
	{
		path.push_back(idxToPos(at));
	}

	std::reverse(path.begin(), path.end());
	return path;
}

int Map::posToIdx(const Vec2& pos) const
{
	return pos.y * mWidth + pos.x;
}

Vec2 Map::idxToPos(int idx) const
{
	int x = idx % mWidth;
	int y = idx / mWidth;
	return Vec2{x, y};
}

MapCell* Map::getCell(const Vec2& pos)
{
	if (not isValidPos(pos))
	{
		return nullptr;
	}

	return &mMapCells[posToIdx(pos)];
}

bool Map::isValidPos(const Vec2& pos) const
{
	return pos.x >= 0 && pos.x < mWidth && pos.y >= 0 && pos.y < mHeight;
}

void Map::addUnit(Unit& unit, const Vec2& pos) {
	if (mUnitToPosition.count(&unit))
	{
		throw std::runtime_error(std::format("Unit {} already on the map", unit.getId()));
	}

	auto cell = getCell(pos);
	if (not cell)
	{
		throw std::runtime_error(std::format("Wrong position {}x{} for unit {}", pos.x, pos.y, unit.getId()));
	}

	mUnitToPosition[&unit] = pos;
	cell->unitList.push_back(&unit);
}

void Map::removeUnit(Unit& unit) {
	auto it = mUnitToPosition.find(&unit);
	if (it == mUnitToPosition.end())
	{
		return;
	}

	if (auto cell = getCell(it->second))
	{
		if (auto it = std::find(cell->unitList.begin(), cell->unitList.end(), &unit); it != cell->unitList.end())
		{
			cell->unitList.erase(it);
		}
	}

	mUnitToPosition.erase(it);
}

void Map::moveUnit(Unit& unit, const Vec2 pos) {
	auto it = mUnitToPosition.find(&unit);
	if (it == mUnitToPosition.end())
	{
		throw std::runtime_error(std::format("Unit {} is not on the map", unit.getId()));
	}

	auto newCell = getCell(pos);
	if (not newCell)
	{
		throw std::runtime_error(std::format("Wrong position {}x{} for unit {}", pos.x, pos.y, unit.getId()));
	}

	auto oldCell = getCell(it->second);
	if (not oldCell)
	{
		// Вообще это ошибка, но где-то внутри логики текущего класса
		return;
	}

	auto& oldList = oldCell->unitList;
	auto listIt = std::find(oldList.begin(), oldList.end(), &unit);
	if (listIt != oldList.end())
	{
		auto& newList = newCell->unitList;
		newList.splice(newList.end(), oldList, listIt);
	}
}
