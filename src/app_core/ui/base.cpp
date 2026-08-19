#include "app_core/ui/base.hpp"
#include "raylib.h"
#include <memory>
#include <utility>
#include <vector>

constexpr float c_half = 0.5F;

namespace AppCore::UI {
// Add child to hierarchy
auto UIElement::addChild(std::shared_ptr<UIElement> child) -> void {
  child->m_parent = weak_from_this();
  m_children.push_back(std::move(child));
}

// --- PASS 1: Layout Calculation ---
auto UIElement::computeLayout(Rectangle parentBounds) -> void {
  // 1. Compute local position relative to anchor
  Vector2 anchorPos = getAnchorPosition(parentBounds, m_constraints.anchor);

  m_computedBounds = Rectangle{
      .x = anchorPos.x + m_constraints.offset.x,
      .y = anchorPos.y + m_constraints.offset.y,
      .width = m_constraints.size.x,
      .height = m_constraints.size.y,
  };

  // 2. Recursively compute children layout
  for (auto &child : m_children) {
    child->computeLayout(m_computedBounds);
  }
}

// --- PASS 2: Input & Rendering ---
auto UIElement::update(Vector2 mousePos, bool mouseClicked) -> void {
  for (auto &child : m_children) {
    child->update(mousePos, mouseClicked);
  }
}

auto UIElement::render() -> void {
  for (auto &child : m_children) {
    child->render();
  }
}

auto UIElement::setConstraints(LayoutConstraints constraints) -> void {
  m_constraints = constraints;
}

[[nodiscard]] auto UIElement::getComputedBounds() const -> Rectangle {
  return m_computedBounds;
}

auto UIElement::getChildren() -> std::vector<std::shared_ptr<UIElement>> & {
  return m_children;
}

auto UIElement::getAnchorPosition(Rectangle parent, Anchor anchor) -> Vector2 {
  switch (anchor) {
  case Anchor::TopLeft:
    return {
        .x = parent.x,
        .y = parent.y,
    };
  case Anchor::TopCenter:
    return {
        .x = parent.x + (parent.width * c_half),
        .y = parent.y,
    };
  case Anchor::TopRight:
    return {
        .x = parent.x + parent.width,
        .y = parent.y,
    };
  case Anchor::Center:
    return {
        .x = parent.x + (parent.width * c_half),
        .y = parent.y + (parent.height * c_half),
    };
  case Anchor::BottomLeft:
    return {
        .x = parent.x,
        .y = parent.y + parent.height,
    };
  case Anchor::BottomCenter:
    return {
        .x = parent.x + (parent.width * c_half),
        .y = parent.y + parent.height,
    };
  case Anchor::BottomRight:
    return {
        .x = parent.x + parent.width,
        .y = parent.y + parent.height,
    };
  }
  return {
      .x = parent.x,
      .y = parent.y,
  };
}
} // namespace AppCore::UI
