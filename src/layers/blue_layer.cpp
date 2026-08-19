#include "layers/blue_layer.hpp"
#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include "raylib.h"
#include <print>

BlueLayer::BlueLayer(AppCore::EventManager &eventManager)
    : AppCore::ILayer(eventManager) {}

auto BlueLayer::onAttach() -> void { std::println("Blue layer attached"); }

auto BlueLayer::onDetach() -> void {}

auto BlueLayer::onRender() -> void {
  constexpr int posX = 0;
  constexpr int posY = 0;
  constexpr int width = 50;
  constexpr int height = 50;

  DrawRectangle(posX, posY, width, height, BLUE);
}

auto BlueLayer::onUpdate() -> void {}
