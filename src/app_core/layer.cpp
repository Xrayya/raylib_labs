#include "layer.hpp"
#include "app_core/event.hpp"

namespace AppCore {
Layer::Layer(EventBus &eventBus) : m_eventBus(eventBus) {}
} // namespace AppCore
