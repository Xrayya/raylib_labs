#pragma once

#include <any>
#include <concepts>
#include <cstdint>
#include <functional>
#include <typeindex>

namespace AppCore {
template <typename T>
concept ValidEvent = requires(T e) {
  { e.timestamp } -> std::convertible_to<uint64_t>;
  { e.handled } -> std::convertible_to<bool>;
};

class EventBus {
private:
  std::unordered_map<std::type_index,
                     std::vector<std::function<void(const std::any &)>>>
      listeners;

public:
  template <ValidEvent T>
  auto subscribe(std::function<void(const T &)> callback) -> void {
    listeners[typeid(T)].push_back(
        [callback](const std::any &genericEvent) -> void {
          callback(std::any_cast<const T &>(genericEvent));
        });
  }

  template <ValidEvent T> auto publish(const T &event) -> void {
    std::type_index id = typeid(T);

    if (listeners.contains(id)) {
      std::any wrappedEvent = event;
      for (const auto &callback : listeners[id]) {
        callback(wrappedEvent);
      }
    }
  }
};
} // namespace AppCore
