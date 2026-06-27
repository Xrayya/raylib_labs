#include "overlay_layer.hpp"
#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include "imgui.h"

OverlayLayer::OverlayLayer(AppCore::EventBus &eventBus)
    : AppCore::Layer(eventBus) {}

auto OverlayLayer::onRender() -> void {
  if (ImGui::Begin("Switch Layer Button")) {
    ImGui::Button("Swtich layer");
  }
  ImGui::End();
}

auto OverlayLayer::onUpdate() -> void {}
