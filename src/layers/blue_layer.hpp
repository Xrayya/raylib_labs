#pragma once

#include "app_core/event.hpp"
#include "app_core/layer.hpp"

class BlueLayer : public AppCore::Layer {
public:
  BlueLayer(AppCore::EventBus &);

  auto onRender() -> void override;
  auto onUpdate() -> void override;
};
