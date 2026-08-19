#pragma once

#include "layers/appui_test_layer.hpp"
#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include "app_core/ui/base.hpp"
#include "app_core/ui/button.hpp"
#include "app_core/ui/stack_panel.hpp"
#include "raylib.h"
#include <memory>
#include <print>

AppUITestLayer::AppUITestLayer(AppCore::EventManager &eventManager)
    : AppCore::ILayer(eventManager) {}

auto AppUITestLayer::onAttach() -> void {
  std::println("entering onAttach");
  // 1. Root panel covering the screen or centered modal
  m_uiRoot = std::make_shared<AppCore::UI::UIElement>();

  constexpr float c_stackPanelSpacing = 15.0F;
  constexpr float c_stackPanelPaddingX = 20.0F;
  constexpr float c_stackPanelPaddingY = 20.0F;
  constexpr float c_stackPanelOffsetX = -150.0F;
  constexpr float c_stackPanelOffsetY = -200.0F;
  constexpr float c_stackPanelSizeX = 300.0F;
  constexpr float c_stackPanelSizeY = 400.0F;

  // 2. Centered Vertical Auto-Layout Stack
  auto panel = std::make_shared<AppCore::UI::StackPanel>(
      AppCore::UI::LayoutDirection::Vertical, c_stackPanelSpacing,
      Vector2{
          .x = c_stackPanelPaddingX,
          .y = c_stackPanelPaddingY,
      });
  panel->setConstraints({
      .offset =
          {
              .x = c_stackPanelOffsetX,
              .y = c_stackPanelOffsetY,
          }, // Center origin shift
      .size =
          {
              .x = c_stackPanelSizeX,
              .y = c_stackPanelSizeY,
          },
      .anchor = AppCore::UI::Anchor::Center,
  });

  constexpr float c_btnStartSizeX = 260.0F;
  constexpr float c_btnStartSizeY = 45.0F;

  // 3. Add Buttons to auto-layout stack
  auto btnStart = std::make_shared<AppCore::UI::Button>(
      "Start Game", []() -> void { TraceLog(LOG_INFO, "Start Clicked!"); });
  btnStart->setConstraints({
      .size =
          {
              .x = c_btnStartSizeX,
              .y = c_btnStartSizeY,
          },
  });

  constexpr float c_btnOptionsSizeX = 260.0F;
  constexpr float c_btnOptionsSizeY = 45.0F;

  auto btnOptions = std::make_shared<AppCore::UI::Button>(
      "Options", []() -> void { TraceLog(LOG_INFO, "Options Clicked!"); });
  btnOptions->setConstraints({
      .size =
          {
              .x = c_btnOptionsSizeX,
              .y = c_btnOptionsSizeY,
          },
  });

  // Build hierarchy
  panel->addChild(btnStart);
  panel->addChild(btnOptions);
  m_uiRoot->addChild(panel);
}

auto AppUITestLayer::onDetach() -> void {}

auto AppUITestLayer::onRender() -> void { m_uiRoot->render(); }

auto AppUITestLayer::onUpdate() -> void {
  // Pass 1: Recalculate layout based on screen resolution
  Rectangle screenBounds{
      .x = 0,
      .y = 0,
      .width = static_cast<float>(GetScreenWidth()),
      .height = static_cast<float>(GetScreenHeight()),
  };

  m_uiRoot->setConstraints({
      .offset =
          {
              .x = 0.0F,
              .y = 0.0F,
          },
      .size =
          {
              .x = screenBounds.width,
              .y = screenBounds.height,
          },
      .anchor = AppCore::UI::Anchor::TopLeft,
  });

  m_uiRoot->computeLayout(screenBounds);

  // Pass 2: Process interactions
  Vector2 mousePos = GetMousePosition();
  bool mouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  m_uiRoot->update(mousePos, mouseClicked);
}
