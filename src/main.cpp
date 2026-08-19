#include "app_core/application.hpp"
#include "layers/blue_layer.hpp"
#include "layers/overlay_layer.hpp"
#include "layers/red_layer.hpp"
#include <cstdio>

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

  app.pushLayer<RedLayer>();
  app.pushLayer<BlueLayer>();
  app.pushLayer<OverlayLayer>();

  app.run();

  getchar();
  return 0;
}
