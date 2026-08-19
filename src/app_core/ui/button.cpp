#include "app_core/ui/button.hpp"
#include "app_core/ui/base.hpp"
#include "raylib.h"
#include <functional>
#include <string>
#include <utility>

constexpr float c_half = 0.5F;

namespace AppCore::UI {
Button::Button(std::string text, std::function<void()> onClick)
    : m_text(std::move(text)), m_onClick(std::move(onClick)) {}

auto Button::update(Vector2 mousePos, bool mouseClicked) -> void {
  m_isHovered = CheckCollisionPointRec(mousePos, getComputedBounds());
  if (m_isHovered && mouseClicked && m_onClick) {
    m_onClick();
  }

  // Process potential children
  UIElement::update(mousePos, mouseClicked);
}

auto Button::render() -> void {
  Color background = m_isHovered ? LIGHTGRAY : GRAY;
  DrawRectangleRec(getComputedBounds(), background);
  DrawRectangleLinesEx(getComputedBounds(), 2, DARKGRAY);

  // Center text inside computed bounds
  constexpr int c_fontSize = 20;
  int textWidth = MeasureText(m_text.c_str(), c_fontSize);
  float textX =
      getComputedBounds().x +
      ((getComputedBounds().width - static_cast<float>(textWidth)) * c_half);
  float textY = getComputedBounds().y +
                ((getComputedBounds().height - c_fontSize) * c_half);

  DrawText(m_text.c_str(), static_cast<int>(textX), static_cast<int>(textY),
           c_fontSize, BLACK);

  UIElement::render();
}
} // namespace AppCore::UI
