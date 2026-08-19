#include "app_core/application.hpp"
#include "app_core/layer.hpp"
#include "raylib.h"
#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

namespace AppCore {
CApplication::CApplication(const SApplicationSpec &spec) {
  m_eventManager.subscribe<SSwapLayerEvent>(
      [this](SSwapLayerEvent &event) -> void {
        this->swapLayer(event.layer1Idx, event.layer2Idx);
        event.handled = true;
      });

  InitWindow(spec.width, spec.height, spec.appName.c_str());
  SetTargetFPS(spec.targetFPS);
}

auto CApplication::pushLayer(std::unique_ptr<ILayer> nextLayer) -> void {
  auto *newLayer = nextLayer.get();
  m_layerStack.push_back(std::move(nextLayer));
  newLayer->onAttach();
}

auto CApplication::swapLayer(const size_t &layer1Idx, const size_t &layer2Idx)
    -> void {
  assert(layer1Idx <= m_layerStack.size() - 1 && "Out of bound for layer1Idx");
  assert(layer2Idx <= m_layerStack.size() - 1 && "Out of bound for layer2Idx");

  std::swap(m_layerStack[layer1Idx], m_layerStack[layer2Idx]);
}

auto CApplication::run() -> void {
  while (!WindowShouldClose()) {
    for (const auto &layer : m_layerStack) {
      layer->onUpdate();
    }

    BeginDrawing();
    ClearBackground(BLACK);

    for (const auto &layer : m_layerStack) {
      layer->onRender();
    }

    EndDrawing();
  }

  CloseWindow();
}
} // namespace AppCore
