#pragma once

#include "app_core/event.hpp"
#include "app_core/layer.hpp"

class OverlayLayer : public AppCore::Layer {
public:
  OverlayLayer(AppCore::EventBus &);

  auto onRender() -> void override;
  auto onUpdate() -> void override;
};
