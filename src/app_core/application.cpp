#include "app_core/application.hpp"
#include "app_core/layer.hpp"
#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

namespace AppCore {
auto CApplication::pushLayer(std::unique_ptr<ILayer> nextLayer) -> void {
  m_layerStack.push_back(std::move(nextLayer));
}

auto CApplication::swapLayer(size_t layer1Idx, size_t layer2Idx) -> void {
  assert(layer1Idx <= m_layerStack.size() - 1 &&
         layer2Idx <= m_layerStack.size());

  std::swap(m_layerStack[layer1Idx], m_layerStack[layer2Idx]);
}
} // namespace AppCore
