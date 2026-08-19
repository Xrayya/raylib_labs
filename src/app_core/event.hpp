#pragma once

#include <concepts>
#include <cstdint>
#include <functional>
#include <memory>
#include <queue>
#include <ranges>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

namespace AppCore {
template <typename TEvent>
concept ValidEvent = requires(TEvent eventType) {
  { eventType.handled } -> std::same_as<bool &>;
};

using SubscriptionId = uint64_t;

class EventManager {
public:
  template <ValidEvent TEvent>
  auto subscribe(std::function<void(TEvent &)> callback) -> SubscriptionId {
    const SubscriptionId &listenerId = m_nextId++;

    m_listeners[typeid(TEvent)].push_back({
        .id = listenerId,
        .callback = [callback](void *genericEvent) -> void {
          auto *castedEvent = static_cast<TEvent *>(genericEvent);
          if (!castedEvent->handled) {
            callback(*castedEvent);
          }
        },
    });

    return listenerId;
  }

  template <ValidEvent TEvent> auto unsubscribe(SubscriptionId subId) -> void {
    const std::type_index &typeIdx = typeid(TEvent);
    if (!m_listeners.contains(typeIdx)) {
      return;
    }

    auto &typeIdListeners = m_listeners[typeIdx];
    std::erase_if(typeIdListeners,
                  [subId](const SRegisteredListener &item) -> auto {
                    return item.id == subId;
                  });
  }

  template <ValidEvent TEvent> auto enqueue(TEvent event) -> void {
    auto storedEvent = std::make_shared<TEvent>(std::move(event));
    m_eventQueue.push(
        [this, storedEvent]() mutable -> auto { this->publish(*storedEvent); });
  }

  auto processEvents() -> void;

private:
  struct SRegisteredListener {
    SubscriptionId id;
    std::function<void(void *)> callback;
  };

  std::unordered_map<std::type_index, std::vector<SRegisteredListener>>
      m_listeners;
  std::queue<std::function<void()>> m_eventQueue;

  SubscriptionId m_nextId = 1;

  template <ValidEvent TEvent> auto publish(TEvent &event) -> void {
    const std::type_index &typeIdx = typeid(TEvent);

    if (!m_listeners.contains(typeIdx)) {
      return;
    }

    auto typeIdListeners = m_listeners[typeIdx];
    for (const auto &listener : std::ranges::reverse_view(typeIdListeners)) {
      if (event.handled) {
        break;
      }
      listener.callback(&event);
    }
  }
};
} // namespace AppCore
