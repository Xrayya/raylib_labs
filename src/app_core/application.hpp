#pragma once

#include "app_core/layer.hpp"
#include <cstddef>
#include <memory>
#include <vector>

namespace AppCore {
class CApplication {
public:
  auto pushLayer(std::unique_ptr<ILayer> nextLayer) -> void;
  auto swapLayer(size_t layer1Idx, size_t layer2Idx) -> void;

private:
  std::vector<std::unique_ptr<ILayer>> m_layerStack;
};
} // namespace AppCore
