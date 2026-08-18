#pragma once

namespace AppCore {
class ILayer {
public:
  auto onInit() -> void;
  auto onDestroy() -> void;
  auto onAttach() -> void;
  auto onDetach() -> void;
  auto onRender() -> void;
};
} // namespace AppCore
