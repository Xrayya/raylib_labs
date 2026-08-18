#pragma once

#include "app_core/layer.hpp"
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

  auto pushLayer(std::unique_ptr<ILayer> nextLayer) -> void;
  auto swapLayer(const size_t &layer1Idx, const size_t &layer2Idx) -> void;

  auto run() -> void;

private:
  std::vector<std::unique_ptr<ILayer>> m_layerStack;
};
} // namespace AppCore
