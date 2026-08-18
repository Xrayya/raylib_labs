#include "layers/red_layer.hpp"
#include "raylib.h"

auto RedLayer::onInit() -> void {}

auto RedLayer::onDestroy() -> void {}

auto RedLayer::onAttach() -> void {}

auto RedLayer::onDetach() -> void {}

auto RedLayer::onRender() -> void {
  constexpr int posX = 25;
  constexpr int posY = 25;
  constexpr int width = 50;
  constexpr int height = 50;

  DrawRectangle(posX, posY, width, height, RED);
}
