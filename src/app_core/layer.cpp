#pragma once

#include "app_core/layer.hpp"
#include "app_core/event.hpp"

namespace AppCore {
ILayer::ILayer(EventManager &EventManager) : m_eventManager(EventManager) {}

auto ILayer::getEventBus() -> EventManager & { return m_eventManager; }
} // namespace AppCore
