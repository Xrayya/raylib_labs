#pragma once

#include "app_core/layer.hpp"
#include "raylib.h"

class OverlayLayer : public AppCore::ILayer {
public:
  auto onInit() -> void override;
  auto onDestroy() -> void override;
  auto onAttach() -> void override;
  auto onDetach() -> void override;
  auto onRender() -> void override;
  auto onUpdate() -> void override;

private:
  Rectangle m_btnRect;
};
