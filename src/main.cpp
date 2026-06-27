#include "app_core/application.hpp"
#include "layers/overlay_layer.hpp"
#include "layers/red_layer.hpp"
#include <cstdio>

auto main() -> int {
  AppCore::ApplicationSpec appSpec = {.name = "Raylib Things"};

  AppCore::Application app(appSpec);
  app.pushLayer<RedLayer>();
  app.pushLayer<OverlayLayer>();
  app.run();

  getchar();

  return 0;
}
