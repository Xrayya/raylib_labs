#pragma once

#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include "app_core/ui3/root.hpp"

class AppUI3TestLayer : public AppCore::ILayer {
public:
  AppUI3TestLayer(AppCore::EventManager &eventManager);

  auto onAttach() -> void override;
  auto onDetach() -> void override;
  auto onRender() -> void override;
  auto onUpdate() -> void override;

private:
  AppCore::UI3::CRoot m_root;
};
