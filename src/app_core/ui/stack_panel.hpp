#pragma once

#include "app_core/ui/base.hpp"
#include "raylib.h"
#include <cstdint>

namespace AppCore::UI {
enum class LayoutDirection : std::uint8_t { Vertical, Horizontal };

class StackPanel : public UIElement {
public:
  StackPanel(LayoutDirection dir, float spacing, Vector2 padding);

  void computeLayout(Rectangle parentBounds) override;

private:
  LayoutDirection m_direction;
  float m_spacing;
  Vector2 m_padding;
};
} // namespace AppCore::UI
