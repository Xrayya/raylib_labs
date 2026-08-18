#include "app_core/application.hpp"
#include "app_core/layer.hpp"
#include "layers/blue_layer.hpp"
#include "layers/red_layer.hpp"
#include <cstdio>
#include <memory>
#include <utility>

auto main() -> int {
  constexpr int specWidth = 500;
  constexpr int specHeight = 500;
  constexpr int specFPS = 60;

  AppCore::SApplicationSpec spec = {
      .width = specWidth,
      .height = specHeight,
      .appName = "Arch Test",
      .targetFPS = specFPS,
  };

  AppCore::CApplication app(spec);
  std::unique_ptr<AppCore::ILayer> redLayer = std::make_unique<RedLayer>();
  std::unique_ptr<AppCore::ILayer> blueLayer = std::make_unique<BlueLayer>();

  app.pushLayer(std::move(redLayer));
  app.pushLayer(std::move(blueLayer));

  app.run();

  getchar();
  return 0;
}
