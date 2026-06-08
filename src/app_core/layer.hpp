#pragma once

#include "app_core/event.hpp"
#include <functional>

namespace AppCore {
class Layer {
public:
  Layer(EventBus& eventBus);
  ~Layer() = default;

  Layer(const Layer &) = default;
  Layer(Layer &&) = delete;
  auto operator=(const Layer &) -> Layer & = default;
  auto operator=(Layer &&) -> Layer & = delete;

  auto onUpdate() -> void;
  auto onRender() -> void;

private:
  std::reference_wrapper<EventBus> m_eventBus;
};
} // namespace AppCore
