#include "app_core/application.hpp"
#include "app_core/layer.hpp"
#include "raylib.h"
#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

namespace AppCore {
CApplication::CApplication(const SApplicationSpec &spec) {
  InitWindow(spec.width, spec.height, spec.appName.c_str());
  SetTargetFPS(spec.targetFPS);
}

auto CApplication::pushLayer(std::unique_ptr<ILayer> nextLayer) -> void {
  m_layerStack.push_back(std::move(nextLayer));
}

auto CApplication::swapLayer(const size_t &layer1Idx, const size_t &layer2Idx)
    -> void {
  assert(layer1Idx <= m_layerStack.size() - 1 &&
         layer2Idx <= m_layerStack.size());

  std::swap(m_layerStack[layer1Idx], m_layerStack[layer2Idx]);
}

auto CApplication::run() -> void {
  constexpr int posXRect = 100;
  constexpr int posYRect = 100;
  constexpr int widthRect = 100;
  constexpr int heightRect = 50;

  constexpr int posXText = 110;
  constexpr int posYText = 110;
  constexpr int fontSize = 15;

  Rectangle btnRect = {
      .x = posXRect, .y = posYRect, .width = widthRect, .height = heightRect};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    for (const auto &layer : m_layerStack) {
      layer->onRender();
    }

    DrawRectangleRec(btnRect, GRAY);

    DrawText("Switch", posXText, posYText, fontSize, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), btnRect)) {
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        swapLayer(0, 1);
      }
    }

    EndDrawing();
  }

  CloseWindow();
}
} // namespace AppCore
