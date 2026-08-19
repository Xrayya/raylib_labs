#pragma once

#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include <concepts>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace AppCore {
struct SApplicationSpec {
  int width;
  int height;
  std::string appName;
  int targetFPS;
};

class CApplication {
public:
  CApplication(const SApplicationSpec &spec);

  template <typename TLayer>
    requires std::derived_from<TLayer, ILayer> &&
             std::constructible_from<TLayer, EventManager &>
  auto pushLayer() -> void {
    m_layerStack.push_back(std::make_unique<TLayer>(m_eventManager));
  }
  auto pushLayer(std::unique_ptr<ILayer> nextLayer) -> void;
  auto swapLayer(const size_t &layer1Idx, const size_t &layer2Idx) -> void;

  auto run() -> void;

private:
  std::vector<std::unique_ptr<ILayer>> m_layerStack;
  EventManager m_eventManager;
};

struct SSwapLayerEvent {
  bool handled = false;
  size_t layer1Idx{};
  size_t layer2Idx{};
};
} // namespace AppCore
