#include "app_core/ui2/column.hpp"
#include "app_core/ui2/box.hpp"
#include <utility>

namespace AppCore::UI2 {
CColumn::CColumn(SColumnProps props)
    : CBox(props.boxProps), children(std::move(props.children)) {}
} // namespace AppCore::UI2
