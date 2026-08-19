#include "app_core/event.hpp"
#include <utility>

namespace AppCore {
auto EventManager::processEvents() -> void {
  while (!m_eventQueue.empty()) {
    auto dispatch = std::move(m_eventQueue.front());
    m_eventQueue.pop();
    dispatch();
  }
}
} // namespace AppCore
