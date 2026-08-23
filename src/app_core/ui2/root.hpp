#pragma once

#include "app_core/ui2/box.hpp"
#include <memory>

namespace AppCore::UI2 {
class CRoot : public CBox {
public:
  CRoot();

  std::unique_ptr<CBox> child;
};
} // namespace AppCore::UI2
