#include "app_core/ui3/root.hpp"
#include "app_core/ui3/ui_node.hpp"
#include "raylib.h"

namespace AppCore::UI3 {
CRoot::CRoot()
    : IUINode(SUINodeProps{
          .posX = 0.0F,
          .posY = 0.0F,
          .width = static_cast<float>(GetScreenWidth()),
          .height = static_cast<float>(GetScreenHeight()),
      }) {}

auto CRoot::calculateSize() -> void {}

auto CRoot::calculateLayout() -> void { child->calculateLayout(); }

auto CRoot::draw() -> void { child->draw(); }
} // namespace AppCore::UI3
