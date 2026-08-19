#pragma once

#include "app_core/ui/base.hpp"
#include "raylib.h"
#include <functional>
#include <string>

namespace AppCore::UI {
class Button : public UIElement {
public:
  Button(std::string text, std::function<void()> onClick);

  auto update(Vector2 mousePos, bool mouseClicked) -> void override;

  auto render() -> void override;

private:
  std::string m_text;
  std::function<void()> m_onClick;
  bool m_isHovered = false;
};
} // namespace AppCore::UI
