#pragma once

#include "app_core/ui3/ui_node.hpp"
#include <memory>
#include <vector>

namespace AppCore::UI3 {
struct SColumnProps {
  float spacing = 0.0F;
  float padding = 0.0F;
};

class CColumn : public IUINode {
public:
  CColumn(SColumnProps props);

  float padding;
  float spacing;
  std::vector<std::unique_ptr<IUINode>> children;

  auto calculateSize() -> void override;

  auto calculateLayout() -> void override;

  auto draw() -> void override;
};
} // namespace AppCore::UI3
