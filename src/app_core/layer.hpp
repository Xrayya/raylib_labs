#pragma once

namespace AppCore {
class ILayer {
public:
  ILayer() = default;

  ILayer(const ILayer &) = default;
  ILayer(ILayer &&) = delete;
  auto operator=(const ILayer &) -> ILayer & = default;
  auto operator=(ILayer &&) -> ILayer & = delete;

  virtual ~ILayer() = default;

  virtual auto onInit() -> void = 0;
  virtual auto onDestroy() -> void = 0;
  virtual auto onAttach() -> void = 0;
  virtual auto onDetach() -> void = 0;
  virtual auto onRender() -> void = 0;
};
} // namespace AppCore
