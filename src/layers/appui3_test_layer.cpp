#include "layers/appui3_test_layer.hpp"
#include "app_core/event.hpp"
#include "app_core/layer.hpp"

AppUI3TestLayer::AppUI3TestLayer(AppCore::EventManager &eventManager)
    : AppCore::ILayer(eventManager) {}

auto AppUI3TestLayer::onAttach() -> void {}

auto AppUI3TestLayer::onDetach() -> void {}

auto AppUI3TestLayer::onRender() -> void {}

auto AppUI3TestLayer::onUpdate() -> void {}
