#pragma once

#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include "app_core/ui/base.hpp"
#include <memory>

class AppUITestLayer : public AppCore::ILayer {
public:
  AppUITestLayer(AppCore::EventManager &eventManager);

  auto onAttach() -> void override;
  auto onDetach() -> void override;
  auto onRender() -> void override;
  auto onUpdate() -> void override;

private:
  std::shared_ptr<AppCore::UI::UIElement> m_uiRoot;
};
