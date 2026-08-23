#include "app_core/application.hpp"
#include "layers/appui_test_layer.hpp"
// #include "layers/blue_layer.hpp"
// #include "layers/overlay_layer.hpp"
// #include "layers/red_layer.hpp"
#include <cstdio>

auto main() -> int {
  constexpr int specWidth = 1000;
  constexpr int specHeight = 1000;
  constexpr int specFPS = 60;

  AppCore::SApplicationSpec spec = {
      .width = specWidth,
      .height = specHeight,
      .appName = "Arch Test",
      .targetFPS = specFPS,
  };

  AppCore::CApplication app(spec);

  // app.pushLayer<RedLayer>();
  // app.pushLayer<BlueLayer>();
  // app.pushLayer<OverlayLayer>();
  app.pushLayer<AppUITestLayer>();

  app.run();

  getchar();
  return 0;
}
