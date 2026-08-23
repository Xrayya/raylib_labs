#include "app_core/ui3/ui_node.hpp"

namespace AppCore::UI3 {
IUINode::IUINode(SUINodeProps props)
    : posX(props.posX), posY(props.posY), width(props.width),
      height(props.height) {}
} // namespace AppCore::UI3
