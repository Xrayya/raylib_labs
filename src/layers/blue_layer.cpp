#include "blue_layer.hpp"
#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include "raylib.h"

BlueLayer::BlueLayer(AppCore::EventBus &eventBus) : AppCore::Layer(eventBus) {}

auto BlueLayer::onRender() -> void {
  constexpr int posX = 5;
  constexpr int posY = 5;
  constexpr int width = 50;
  constexpr int height = 50;

  DrawRectangle(posX, posY, width, height, BLUE);
}

auto BlueLayer::onUpdate() -> void {}
