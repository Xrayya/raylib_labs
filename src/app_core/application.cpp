#include "app_core/application.hpp"
#include "app_core/layer.hpp"
#include "raylib.h"
#include <cassert>
#include <cstddef>
#include <memory>
#include <print>
#include <typeindex>
#include <utility>

namespace AppCore {
CApplication::CApplication(const SApplicationSpec &spec) {
  m_eventManager.subscribe<SPushLayerFromTypeEvent>(
      [this](SPushLayerFromTypeEvent &event) -> void {
        if (event.layerFactory) {
          this->pushLayer(event.layerFactory(m_eventManager));
          event.handled = true;
        }
      });

  m_eventManager.subscribe<SPushLayerFromInstanceEvent>(
      [this](SPushLayerFromInstanceEvent &event) -> void {
        this->pushLayer(std::move(event.layerInstance));
        event.handled = true;
      });

  m_eventManager.subscribe<SSwapLayerEvent>(
      [this](SSwapLayerEvent &event) -> void {
        this->swapLayer(event.layer1Idx, event.layer2Idx);
        event.handled = true;
      });

  m_eventManager.subscribe<SRemoveLayerByIdxEvent>(
      [this](SRemoveLayerByIdxEvent &event) -> void {
        this->removeLayer(event.layerIdx);
        event.handled = true;
      });

  m_eventManager.subscribe<SRemoveLayerByTypeEvent>(
      [this](SRemoveLayerByTypeEvent &event) -> void {
        this->removeLayer(event.typeIndex);
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

auto CApplication::removeLayer(std::type_index &layerTypeIdx) -> void {
  std::println("Enter remove by type");
  size_t targetLayerIdx = 0;
  size_t idx = 0;
  for (; idx < m_layerStack.size(); ++idx) {
    if (typeid(*m_layerStack[idx]) == layerTypeIdx) {
      std::println("Found target");
      targetLayerIdx = idx;
      break;
    }
  }

  if (idx >= m_layerStack.size()) {
    return;
  }

  removeLayer(targetLayerIdx);
}

auto CApplication::removeLayer(size_t layerIdx) -> void {
  assert(layerIdx <= m_layerStack.size() - 1 && "Out of bound for layer1Idx");

  m_layerStack[layerIdx]->onDetach();

  std::swap(m_layerStack[layerIdx], m_layerStack.back());
  m_layerStack.pop_back();
}

auto CApplication::run() -> void {
  while (!WindowShouldClose()) {
    // std::println("Layer Stack Size: {}", m_layerStack.size());
    for (const auto &layer : m_layerStack) {
      layer->onUpdate();
    }

    m_eventManager.processEvents();

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
