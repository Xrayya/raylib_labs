#include "layers/red_layer.hpp"
#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include "raylib.h"
#include <print>

RedLayer::RedLayer(AppCore::EventManager &eventManager)
    : AppCore::ILayer(eventManager) {}

auto RedLayer::onAttach() -> void { std::println("Red layer attached"); }

auto RedLayer::onDetach() -> void {}

auto RedLayer::onRender() -> void {
  constexpr int posX = 25;
  constexpr int posY = 25;
  constexpr int width = 50;
  constexpr int height = 50;

  DrawRectangle(posX, posY, width, height, RED);
}

auto RedLayer::onUpdate() -> void {}
