#include "app_core/ui/stack_panel.hpp"
#include "app_core/ui/base.hpp"
#include "raylib.h"

constexpr float c_defaultSpacing = 10.0F;
constexpr float c_defaultPaddingX = 10.F;
constexpr float c_defaultPaddingY = 10.F;

constexpr float c_double = 2.0F;

namespace AppCore::UI {
StackPanel::StackPanel(LayoutDirection dir, float spacing = c_defaultSpacing,
                       Vector2 padding =
                           {
                               .x = c_defaultPaddingX,
                               .y = c_defaultPaddingY,
                           })
    : m_direction(dir), m_spacing(spacing), m_padding(padding) {}

void StackPanel::computeLayout(Rectangle parentBounds) {
  // Compute own base bounds first
  UIElement::computeLayout(parentBounds);

  float currentX = getComputedBounds().x + m_padding.x;
  float currentY = getComputedBounds().y + m_padding.y;

  for (auto &child : getChildren()) {
    // Create allocated bounds for the child based on stack position
    Rectangle childParentBounds{
        .x = currentX,
        .y = currentY,
        .width = getComputedBounds().width - (m_padding.x * c_double),
        .height = getComputedBounds().height - (m_padding.y * c_double),
    };

    child->computeLayout(childParentBounds);
    Rectangle childBounds = child->getComputedBounds();

    // Advance stack offset based on direction
    if (m_direction == LayoutDirection::Vertical) {
      currentY += childBounds.height + m_spacing;
    } else {
      currentX += childBounds.width + m_spacing;
    }
  }
}
} // namespace AppCore::UI
