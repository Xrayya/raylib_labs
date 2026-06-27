#pragma once

#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include <algorithm>
#include <concepts>
#include <memory>
#include <string>
#include <vector>

namespace AppCore {

struct ApplicationSpec {
  std::string name;
};

class Application {
public:
  Application(ApplicationSpec spec);

  auto run() -> void;

  template <typename TLayer>
    requires std::derived_from<TLayer, Layer> &&
             std::constructible_from<TLayer, EventBus &>
  auto pushLayer() -> void {
    m_layerStack.push_back(std::make_unique<TLayer>(m_eventBus));
  }

  template <typename TLayer>
    requires std::derived_from<TLayer, Layer>
  auto pushLayer(std::unique_ptr<TLayer> layer) -> void {
    m_layerStack.push_back(std::move(layer));
  }

private:
  ApplicationSpec m_spec;
  std::vector<std::unique_ptr<Layer>> m_layerStack;
  EventBus m_eventBus;
};
} // namespace AppCore
