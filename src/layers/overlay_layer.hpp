#pragma once

#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include "raylib.h"

class OverlayLayer : public AppCore::ILayer {
public:
  OverlayLayer(AppCore::EventManager &EventManager);

  auto onAttach() -> void override;
  auto onDetach() -> void override;
  auto onRender() -> void override;
  auto onUpdate() -> void override;

private:
  Rectangle m_btnSwitchRect;
  Rectangle m_btnToggleBlueRect;
  Rectangle m_btnToggleRedRect;

  bool m_blueLayerRegistered = true;
  bool m_redLayerRegistered = true;
};
