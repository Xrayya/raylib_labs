#pragma once

#include "raylib.h"

namespace AppCore::UI2 {
struct SBoxProps {
  float posX = 0.0F;
  float posY = 0.0F;
  float width = 0.0F;
  float height = 0.0F;

  float padding = 0.0F;
};

class CBox {
public:
  CBox(SBoxProps props);

  Rectangle rect;
};
} // namespace AppCore::UI2
