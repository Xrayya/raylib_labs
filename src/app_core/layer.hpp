#pragma once

#include "app_core/event.hpp"
#include <functional>

namespace AppCore {
class Layer {
public:
  Layer(EventBus &eventBus);
  virtual ~Layer() = default;

  Layer(const Layer &) = default;
  Layer(Layer &&) = delete;
  auto operator=(const Layer &) -> Layer & = default;
  auto operator=(Layer &&) -> Layer & = delete;

  virtual auto onUpdate() -> void = 0;
  virtual auto onRender() -> void = 0;

private:
  std::reference_wrapper<EventBus> m_eventBus;
};
} // namespace AppCore
