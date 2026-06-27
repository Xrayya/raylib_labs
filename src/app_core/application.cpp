#include "application.hpp"
#include "raylib.h"
#include "rlImGui.h"

#include <ranges>

namespace AppCore {

Application::Application(ApplicationSpec spec) : m_spec(std::move(spec)) {
  constexpr int screenWidth = 500;
  constexpr int screenHeight = 500;

  constexpr int fps = 60;

  InitWindow(screenWidth, screenHeight, m_spec.name.c_str());
  SetTargetFPS(fps);
  rlImGuiSetup(true);
}

auto Application::run() -> void {

  while (!WindowShouldClose()) {

    for (auto &layer : std::ranges::reverse_view(m_layerStack)) {
      layer->onUpdate();
    }

    BeginDrawing();
    ClearBackground(BLACK);

    rlImGuiBegin();

    for (const auto &layer : m_layerStack) {
      layer->onRender();
    }

    rlImGuiEnd();

    EndDrawing();
  }

  rlImGuiShutdown();
  CloseWindow();
}

} // namespace AppCore
