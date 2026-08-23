#include "app_core/ui2/root.hpp"
#include "app_core/ui2/box.hpp"
#include "raylib.h"

namespace AppCore::UI2 {
CRoot::CRoot()
    : CBox(SBoxProps{
          .width = static_cast<float>(GetScreenWidth()),
          .height = static_cast<float>(GetRenderHeight()),
      }) {}
} // namespace AppCore::UI2
