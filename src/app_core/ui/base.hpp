#pragma once

#include "raylib.h"
#include <cstdint>
#include <memory>
#include <vector>

constexpr float c_defaultOffsetX = 0.0F;
constexpr float c_defaultOffsetY = 0.0F;
constexpr float c_defaultSizeX = 100.0F;
constexpr float c_defaultSizeY = 40.0F;

namespace AppCore::UI {
enum class Anchor : std::uint8_t {
  TopLeft,
  TopCenter,
  TopRight,
  Center,
  BottomLeft,
  BottomCenter,
  BottomRight
};

struct LayoutConstraints {
  Vector2 offset{
      .x = c_defaultOffsetX,
      .y = c_defaultOffsetY,
  }; // Relative offset from anchor
  Vector2 size{
      .x = c_defaultSizeX,
      .y = c_defaultSizeY,
  }; // Width, Height
  Anchor anchor = Anchor::TopLeft;
};

class UIElement : public std::enable_shared_from_this<UIElement> {
public:
  UIElement() = default;

  UIElement(const UIElement &) = default;
  UIElement(UIElement &&) = delete;
  auto operator=(const UIElement &) -> UIElement & = default;
  auto operator=(UIElement &&) -> UIElement & = delete;

  virtual ~UIElement() = default;

  auto addChild(std::shared_ptr<UIElement> child) -> void;

  virtual auto computeLayout(Rectangle parentBounds) -> void;

  virtual auto update(Vector2 mousePos, bool mouseClicked) -> void;

  virtual auto render() -> void;

  auto setConstraints(LayoutConstraints constraints) -> void;

  [[nodiscard]] auto getComputedBounds() const -> Rectangle;

protected:
  auto getChildren() -> std::vector<std::shared_ptr<UIElement>> &;
  auto getChildren() const -> const std::vector<std::shared_ptr<UIElement>> &;

private:
  LayoutConstraints m_constraints;
  Rectangle m_computedBounds = {
      .x = 0,
      .y = 0,
      .width = 0,
      .height = 0,
  };
  std::weak_ptr<UIElement> m_parent;
  std::vector<std::shared_ptr<UIElement>> m_children;

  static auto getAnchorPosition(Rectangle parent, Anchor anchor) -> Vector2;
};
} // namespace AppCore::UI
