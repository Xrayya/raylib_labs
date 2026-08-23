#include "app_core/ui3/button.hpp"
#include "app_core/ui3/ui_node.hpp"
#include "raylib.h"

namespace AppCore::UI3 {
CButton::CButton(const SButtonProps &props)
    : IUINode(SUINodeProps{}), text(props.text), fontSize(props.fontSize),
      color(props.color), padding(props.padding) {}

auto CButton::calculateSize() -> void {
  width =
      static_cast<float>(MeasureText(text.c_str(), fontSize)) + (padding * 2);
  height = static_cast<float>(fontSize) + (padding * 2);
}

auto CButton::calculateLayout() -> void {}

auto CButton::draw() -> void {
  DrawRectangleRec(
      Rectangle{
          .x = posX,
          .y = posY,
          .width = width,
          .height = height,
      },
      color);
  DrawText(text.c_str(), static_cast<int>(posX + padding),
           static_cast<int>(posY + padding), fontSize, color);
}
} // namespace AppCore::UI3
