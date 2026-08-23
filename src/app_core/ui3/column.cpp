#include "app_core/ui3/column.hpp"
#include "app_core/ui3/ui_node.hpp"
#include <algorithm>
#include <memory>

namespace AppCore::UI3 {
CColumn::CColumn(SColumnProps props)
    : IUINode(SUINodeProps{}), padding(props.padding), spacing(props.spacing) {}

auto CColumn::calculateSize() -> void {
  for (const auto &child : children) {
    child->calculateSize();
  }

  width = std::ranges::max_element(
              children, {},
              [](const std::unique_ptr<IUINode> &childPtr) -> float {
                return childPtr->width;
              })
              ->get()
              ->width +
          (padding * 2);
  height =
      std::ranges::fold_left(
          children, 0.0F,
          [](float sum, const std::unique_ptr<IUINode> &childPtr) -> float {
            return sum + childPtr->height;
          }) +
      (static_cast<float>(children.size() - 1) * spacing) + (spacing * 2);
}

auto CColumn::calculateLayout() -> void {
  const float childPosX = posX + padding;
  float childPosY = posY + padding;

  for (const auto &child : children) {
    child->posX = childPosX;
    child->posY = childPosY;

    childPosY += child->height + spacing;
  }

  for (const auto &child : children) {
    child->calculateLayout();
  }
}

auto CColumn::draw() -> void {
  for (const auto &child : children) {
    child->draw();
  }
}
} // namespace AppCore::UI3
