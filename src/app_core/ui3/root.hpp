#pragma once

#include "app_core/ui3/ui_node.hpp"
#include <memory>

namespace AppCore::UI3 {
class CRoot : public IUINode {
public:
  CRoot();

  std::unique_ptr<IUINode> child;

  auto calculateSize() -> void override;

  auto calculateLayout() -> void override;

  auto draw() -> void override;
};
} // namespace AppCore::UI3
