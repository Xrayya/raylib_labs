#pragma once

#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include <concepts>
#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <typeindex>
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
    pushLayer(std::make_unique<TLayer>(m_eventManager));
  }
  auto pushLayer(std::unique_ptr<ILayer> nextLayer) -> void;

  auto swapLayer(const size_t &layer1Idx, const size_t &layer2Idx) -> void;

  auto removeLayer(std::type_index &layerTypeIdx) -> void;
  auto removeLayer(size_t layerIdx) -> void;

  auto run() -> void;

private:
  std::vector<std::unique_ptr<ILayer>> m_layerStack;
  EventManager m_eventManager;
};

struct SPushLayerFromTypeEvent {
  bool handled = false;
  std::function<std::unique_ptr<ILayer>(EventManager &)> layerFactory;

  template <typename TLayer>
    requires std::derived_from<TLayer, ILayer> &&
             std::constructible_from<TLayer, EventManager &>
  static auto create() -> SPushLayerFromTypeEvent {
    return SPushLayerFromTypeEvent{
        .layerFactory =
            [](EventManager &eventManager) -> std::unique_ptr<ILayer> {
          return std::make_unique<TLayer>(eventManager);
        },
    };
  }
};

struct SPushLayerFromInstanceEvent {
  bool handled = false;
  std::unique_ptr<ILayer> layerInstance;
};

struct SSwapLayerEvent {
  bool handled = false;
  size_t layer1Idx{};
  size_t layer2Idx{};
};

struct SRemoveLayerByIdxEvent {
  bool handled = false;
  size_t layerIdx{};
};

struct SRemoveLayerByTypeEvent {
  bool handled = false;
  std::type_index typeIndex;

  template <typename TLayer> static auto create() -> SRemoveLayerByTypeEvent {
    return SRemoveLayerByTypeEvent{
        .typeIndex = typeid(TLayer),
    };
  }
};

} // namespace AppCore
