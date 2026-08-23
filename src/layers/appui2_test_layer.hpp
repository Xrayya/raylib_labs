#pragma once

#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include "app_core/ui2/root.hpp"

class AppUI2TestLayer : public AppCore::ILayer {
public:
  AppUI2TestLayer(AppCore::EventManager &eventManager);

  auto onAttach() -> void override;
  auto onDetach() -> void override;
  auto onRender() -> void override;
  auto onUpdate() -> void override;

private:
  AppCore::UI2::CRoot m_root;
};
