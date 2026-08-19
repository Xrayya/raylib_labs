#pragma once

#include "app_core/event.hpp"
#include <functional>

namespace AppCore {
class ILayer {
public:
  ILayer(EventManager &eventManager);

  ILayer(const ILayer &) = default;
  ILayer(ILayer &&) = delete;
  auto operator=(const ILayer &) -> ILayer & = default;
  auto operator=(ILayer &&) -> ILayer & = delete;

  virtual ~ILayer() = default;

  virtual auto onAttach() -> void = 0;
  virtual auto onDetach() -> void = 0;
  virtual auto onRender() -> void = 0;
  virtual auto onUpdate() -> void = 0;

protected:
  auto getEventBus() -> EventManager &;

private:
  std::reference_wrapper<EventManager> m_eventManager;
};
} // namespace AppCore
