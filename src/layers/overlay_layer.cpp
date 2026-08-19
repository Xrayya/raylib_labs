#include "layers/overlay_layer.hpp"
#include "app_core/application.hpp"
#include "app_core/event.hpp"
#include "app_core/layer.hpp"
#include "layers/blue_layer.hpp"
#include "layers/red_layer.hpp"
#include "raylib.h"
#include <print>

constexpr int posXSwitchRect = 100;
constexpr int posYSwitchRect = 100;
constexpr int widthSwitchRect = 100;
constexpr int heightSwitchRect = 50;

constexpr int posXToggleBlueRect = 100;
constexpr int posYToggleBlueRect = 200;
constexpr int widthToggleBlueRect = 300;
constexpr int heightToggleBlueRect = 50;

constexpr int posXToggleRedRect = 100;
constexpr int posYToggleRedRect = 300;
constexpr int widthToggleRedRect = 300;
constexpr int heightToggleRedRect = 50;

OverlayLayer::OverlayLayer(AppCore::EventManager &eventManager)
    : AppCore::ILayer(eventManager), m_btnSwitchRect({
                                         .x = posXSwitchRect,
                                         .y = posYSwitchRect,
                                         .width = widthSwitchRect,
                                         .height = heightSwitchRect,
                                     }),
      m_btnToggleBlueRect({
          .x = posXToggleBlueRect,
          .y = posYToggleBlueRect,
          .width = widthToggleBlueRect,
          .height = heightToggleBlueRect,
      }),
      m_btnToggleRedRect({
          .x = posXToggleRedRect,
          .y = posYToggleRedRect,
          .width = widthToggleRedRect,
          .height = heightToggleRedRect,
      }) {}

auto OverlayLayer::onAttach() -> void {
  std::println("Overlay layer attached");
}

auto OverlayLayer::onDetach() -> void {}

auto OverlayLayer::onRender() -> void {
  DrawRectangleRec(m_btnSwitchRect, GRAY);
  DrawRectangleRec(m_btnToggleBlueRect, GRAY);
  DrawRectangleRec(m_btnToggleRedRect, GRAY);

  constexpr int posXSwitchText = 110;
  constexpr int posYSwitchText = 110;
  constexpr int fontSwitchSize = 20;

  constexpr int posXToggleBlueText = 110;
  constexpr int posYToggleBlueText = 210;
  constexpr int fontToggleBlueSize = 20;

  constexpr int posXToggleRedText = 110;
  constexpr int posYToggleRedText = 310;
  constexpr int fontToggleRedSize = 20;

  DrawText("Switch", posXSwitchText, posYSwitchText, fontSwitchSize, WHITE);
  DrawText("Toggle Blue Layer", posXToggleBlueText, posYToggleBlueText,
           fontToggleBlueSize, WHITE);
  DrawText("Toggle Red Layer", posXToggleRedText, posYToggleRedText,
           fontToggleRedSize, WHITE);
}

auto OverlayLayer::onUpdate() -> void {
  if (CheckCollisionPointRec(GetMousePosition(), m_btnSwitchRect)) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      AppCore::SSwapLayerEvent event = {.layer1Idx = 0, .layer2Idx = 1};
      getEventBus().enqueue(event);
    }
  }

  if (CheckCollisionPointRec(GetMousePosition(), m_btnToggleBlueRect)) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      if (m_blueLayerRegistered) {
        AppCore::SRemoveLayerByTypeEvent event =
            AppCore::SRemoveLayerByTypeEvent::create<BlueLayer>();
        getEventBus().enqueue(event);
      } else {
        AppCore::SPushLayerFromTypeEvent event =
            AppCore::SPushLayerFromTypeEvent::create<BlueLayer>();
        getEventBus().enqueue(event);
      }

      m_blueLayerRegistered = !m_blueLayerRegistered;
    }
  }

  if (CheckCollisionPointRec(GetMousePosition(), m_btnToggleRedRect)) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      if (m_redLayerRegistered) {
        AppCore::SRemoveLayerByTypeEvent event =
            AppCore::SRemoveLayerByTypeEvent::create<RedLayer>();
        getEventBus().enqueue(event);
      } else {
        AppCore::SPushLayerFromTypeEvent event =
            AppCore::SPushLayerFromTypeEvent::create<RedLayer>();
        getEventBus().enqueue(event);
      }

      m_redLayerRegistered = !m_redLayerRegistered;
    }
  }
}
