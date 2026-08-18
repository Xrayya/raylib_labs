#include "application.hpp"
#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

#include <ranges>
#include <utility>

namespace AppCore {

Application::Application(ApplicationSpec spec) : m_spec(std::move(spec)) {
  constexpr int screenWidth = 1280;
  constexpr int screenHeight = 800;

  constexpr int fps = 60;

  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);

  InitWindow(screenWidth, screenHeight, m_spec.name.c_str());
  SetTargetFPS(fps);
  rlImGuiSetup(true);

  // TODO: make this configured form env var
  constexpr float scale = 2.0F;

  ImGui::GetIO().FontGlobalScale = scale;
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
