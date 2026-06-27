#pragma once

#include "app_core/event.hpp"
#include "app_core/layer.hpp"

class RedLayer : public AppCore::Layer {
public:
  RedLayer(AppCore::EventBus &eventBus);

  auto onRender() -> void override;
  auto onUpdate() -> void override;
};
