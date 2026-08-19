#pragma once

#include "app_core/event.hpp"
#include "app_core/layer.hpp"

class BlueLayer : public AppCore::ILayer {
public:
  BlueLayer(AppCore::EventManager &eventManager);

  auto onAttach() -> void override;
  auto onDetach() -> void override;
  auto onRender() -> void override;
  auto onUpdate() -> void override;
};
