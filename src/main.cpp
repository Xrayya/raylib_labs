#include <raylib.h>

#include <cstdio>
#include <print>

#include "random_rectangle_spawner.hpp"

auto main() -> int {
  randomRectangleSpawner();

  std::print("Press any key to exit...");
  getchar();

  return 0;
}
