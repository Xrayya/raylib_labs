#include "app_core/ui2/box.hpp"

namespace AppCore::UI2 {
CBox::CBox(SBoxProps props)
    : rect({
          .x = props.posX,
          .y = props.posY,
          .width = props.width,
          .height = props.height,
      }) {}
} // namespace AppCore::UI2
