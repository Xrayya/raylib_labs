#include "layers/overlay_layer.hpp"
#include "raylib.h"

auto OverlayLayer::onInit() -> void {
  constexpr int posXRect = 100;
  constexpr int posYRect = 100;
  constexpr int widthRect = 50;
  constexpr int heightRect = 50;

  m_btnRect = {
      .x = posXRect, .y = posYRect, .width = widthRect, .height = heightRect};
}

auto OverlayLayer::onDestroy() -> void {}

auto OverlayLayer::onAttach() -> void {}

auto OverlayLayer::onDetach() -> void {}

auto OverlayLayer::onRender() -> void {
  DrawRectangleRec(m_btnRect, GRAY);

  constexpr int posXText = 105;
  constexpr int posYText = 105;
  constexpr int fontSize = 10;

  DrawText("Switch", posXText, posYText, fontSize, WHITE);
}

auto OverlayLayer::onUpdate() -> void {
  // if (CheckCollisionPointRec(GetMousePosition(), m_btnRect)) {
  //   if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
  //     std::println("INFO: Button Clicked");
  //   }
  // }
}
