#pragma once

namespace AppCore::UI3 {
struct SUINodeProps {
  float posX = 0.0F;
  float posY = 0.0F;
  float width = 0.0F;
  float height = 0.0F;
};

class IUINode {
public:
  IUINode(SUINodeProps props);

  IUINode(const IUINode &) = default;
  IUINode(IUINode &&) = delete;
  auto operator=(const IUINode &) -> IUINode & = default;
  auto operator=(IUINode &&) -> IUINode & = delete;

  virtual ~IUINode() = default;

  virtual auto calculateSize() -> void = 0;

  virtual auto calculateLayout() -> void = 0;

  virtual auto draw() -> void = 0;

  float posX;
  float posY;
  float width;
  float height;
};
} // namespace AppCore::UI3
