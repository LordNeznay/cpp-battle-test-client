
#include <stdexcept>
#include <memory>
#include <optional>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <type_traits>
#include <utility>
#include <functional>
#include <format>
#include <sstream>

#include "game/base/Vec2.hpp"

using UnitId = uint32_t;

// Вкл-выкл дебажные логи с отображением карты
constexpr bool sEnableDebugLogs = true;
// Лимит на шаги симуляции - защита от зацикливания
constexpr int sMaxSimulationSteps = 100;
