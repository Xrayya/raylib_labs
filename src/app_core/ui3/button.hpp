#pragma once

#include "app_core/ui3/ui_node.hpp"
#include "raylib.h"
#include <string>

namespace AppCore::UI3 {
struct SButtonProps {
  std::string text;
  float padding;
  int fontSize;
  Color color;
};

class CButton : public IUINode {
public:
  CButton(const SButtonProps &props);

  std::string text;
  int fontSize;
  Color color;

  float padding;

  auto calculateSize() -> void override;

  auto calculateLayout() -> void override;

  auto draw() -> void override;
};
} // namespace AppCore::UI3
