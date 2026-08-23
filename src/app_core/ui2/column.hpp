#pragma once

#include "app_core/ui2/box.hpp"
#include <memory>
#include <vector>

namespace AppCore::UI2 {
struct SColumnProps {
  SBoxProps boxProps;
  std::vector<std::unique_ptr<CBox>> children =
      std::vector<std::unique_ptr<CBox>>(0);
};

class CColumn : public CBox {
public:
  CColumn(SColumnProps props);

  std::vector<std::unique_ptr<CBox>> children;
};
} // namespace AppCore::UI2
