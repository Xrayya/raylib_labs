#include "layers/appui2_test_layer.hpp"
#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include "app_core/ui2/box.hpp"

AppUI2TestLayer::AppUI2TestLayer(AppCore::EventManager &eventManager)
    : AppCore::ILayer(eventManager) {}

auto AppUI2TestLayer::onAttach() -> void {
  AppCore::UI2::CBox test({
      .padding = 1.0F,
  });
}

auto AppUI2TestLayer::onDetach() -> void {}

auto AppUI2TestLayer::onRender() -> void {}

auto AppUI2TestLayer::onUpdate() -> void {}
