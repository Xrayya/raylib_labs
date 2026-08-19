#include "layers/overlay_layer.hpp"
#include "app_core/application.hpp"
#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include "raylib.h"
#include <print>

constexpr int posXRect = 100;
constexpr int posYRect = 100;
constexpr int widthRect = 100;
constexpr int heightRect = 50;

OverlayLayer::OverlayLayer(AppCore::EventManager &eventManager)
    : AppCore::ILayer(eventManager), m_btnRect({
                                         .x = posXRect,
                                         .y = posYRect,
                                         .width = widthRect,
                                         .height = heightRect,
                                     }) {}

auto OverlayLayer::onInit() -> void {}

auto OverlayLayer::onDestroy() -> void {}

auto OverlayLayer::onAttach() -> void { std::println("Overlay layer attached"); }

auto OverlayLayer::onDetach() -> void {}

auto OverlayLayer::onRender() -> void {
  DrawRectangleRec(m_btnRect, GRAY);

  constexpr int posXText = 110;
  constexpr int posYText = 110;
  constexpr int fontSize = 20;

  DrawText("Switch", posXText, posYText, fontSize, WHITE);
}

auto OverlayLayer::onUpdate() -> void {
  if (CheckCollisionPointRec(GetMousePosition(), m_btnRect)) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      AppCore::SSwapLayerEvent event = {.layer1Idx = 0, .layer2Idx = 1};
      getEventBus().publish(event);
    }
  }
}
