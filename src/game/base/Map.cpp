#include "Map.hpp"
#include <stack>
#include <queue>
#include <sstream>

#include "game/base/Unit.hpp"
#include "game/aspects/PositionAspect.hpp"

// По часовой стрелке с LT
const std::vector<Vec2> Map::sDefaultWalkDirections = {{-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}};

Map::Map(int w, int h) :
	mWidth(w),
	mHeight(h)
{
	mMapCells.resize(mWidth * mHeight);
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
	// Реализация поиска в ширину
	std::vector<Vec2> path;

	if (!isValidPos(from) || !isValidPos(to))
	{
		return path;
	}

	std::queue<Vec2> queue;
	std::unordered_map<int, int> cameFrom;
	std::vector<bool> visited(mWidth * mHeight, false);

	queue.push(from);
	visited[posToIdx(from)] = true;

	while (!queue.empty())
	{
		Vec2 current = queue.front();
		queue.pop();

		if (current.x == to.x && current.y == to.y)
		{
			break;
		}

		for (const Vec2& dir : sDefaultWalkDirections)
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

			queue.push(next);
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

void Map::forEachCellInRadius(const Vec2& center, int radiusMin, int radiusMax, const forEachCellInRadiusCb& visitCb)
{
	if (radiusMin < 0 || radiusMax < radiusMin)
	{
		return;
	}

	std::queue<Vec2> queue;
	std::vector<bool> visited(mWidth * mHeight, false);

	queue.push(center);
	visited[posToIdx(center)] = true;

	while (!queue.empty())
	{
		Vec2 current = queue.front();
		queue.pop();

		int dx = std::abs(current.x - center.x);
		int dy = std::abs(current.y - center.y);
		int dist = dx + dy;

		if (dist > radiusMax)
		{
			continue;
		}

		if (dist >= radiusMin)
		{
			visitCb(current, *getCell(current));
		}

		for (const Vec2& dir : sDefaultWalkDirections)
		{
			Vec2 next = {current.x + dir.x, current.y + dir.y};
			if (!isValidPos(next))
			{
				continue;
			}

			int idx = posToIdx(next);
			if (!visited[idx])
			{
				visited[idx] = true;
				queue.push(next);
			}
		}
	}
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

const MapCell* Map::getCell(const Vec2& pos) const
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
	unit.addAspect(aspect::Position(pos));
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
	unit.removeAspect<aspect::Position>();
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

	if (auto data = unit.getAspect<aspect::Position>())
	{
		data->mPos = pos;
	}

	it->second = pos;
}

std::string Map::makeDebugView() const
{
	std::stringstream ss;

	const auto AddLine = [&]() {
		for (int x = 0; x < mWidth + 1; ++x)
		{
			ss << (x == 0 ? "+---++" : "---+");
		}
		ss << "\n";
	};

	AddLine();
	for (int x = 0; x < mWidth + 1; ++x)
	{
		if (x == 0)
		{
			ss << "|";
		}

		ss << std::format("{:^3}|", x - 1);

		if (x == 0)
		{
			ss << "|";
		}
	}
	ss << "\n";
	AddLine();
	AddLine();

	for (int y = 0; y < mHeight; ++y)
	{
		ss << std::format("|{:^3}||", y);

		for (int x = 0; x < mWidth; ++x)
		{
			auto unitId = [&]() -> std::optional<UnitId>
			{
				if (auto cell = getCell(Vec2{x, y}))
				{
					if (not cell->unitList.empty())
					{
						return cell->unitList.front()->getId();
					}
				}
				return std::nullopt;
			}();

			if (unitId)
			{
				ss << std::format("{:^3}", *unitId);
			}
			else
			{
				ss << "   ";
			}

			ss << "|";
		}
		ss << "\n";

		AddLine();
	}

	return ss.str();
}
