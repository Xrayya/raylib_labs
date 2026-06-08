#include "random_rectangle_spawner.hpp"

#include <chrono>
#include <print>
#include <random>
#include <vector>

#include "raylib.h"
#include "time.hpp"

const float TICK_PER_SECOND = 8;

template <typename T>
inline auto generateRandomNum(T min, T max) -> T {
  unsigned long seed = static_cast<unsigned long>(
      std::chrono::system_clock::now().time_since_epoch().count());
  static std::mt19937 engine(seed);

  if constexpr (std::is_integral_v<T>) {
    std::uniform_int_distribution<T> dist(min, max);
    return dist(engine);
  } else {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(engine);
  }
}

auto randomRectangleSpawner() -> void {
  const float tick_interval = 1.0F / TICK_PER_SECOND;
  float tick_accumulator = 0;

  std::vector<std::pair<Rectangle, Color>> rects;

  InitWindow(1000, 1000, "Click Random Rectangle");

  SetTargetFPS(60);

  TimeContext time_ctx;

  time_ctx.resetTime();

  while (!WindowShouldClose()) {
    time_ctx.update();

    tick_accumulator += time_ctx.getDeltaTime();

    if (tick_accumulator < tick_interval) {
      continue;
    }

    BeginDrawing();

    ClearBackground(BLACK);

    Rectangle btnBounds = {.x = 400, .y = 900, .width = 200, .height = 50};

    std::println("INFO: Spawning Rectangle");
    rects.push_back(std::make_pair<Rectangle, Color>(
        {
            .x = generateRandomNum<float>(0, 1000),
            .y = generateRandomNum<float>(0, 1000),
            .width = generateRandomNum<float>(0, 500),
            .height = generateRandomNum<float>(0, 500),
        },
        {
            .r = static_cast<unsigned char>(generateRandomNum<int>(0, 255)),
            .g = static_cast<unsigned char>(generateRandomNum<int>(0, 255)),
            .b = static_cast<unsigned char>(generateRandomNum<int>(0, 255)),
            .a = static_cast<unsigned char>(generateRandomNum<int>(0, 255)),
        }));

    for (const auto& [rect, color] : rects) {
      DrawRectangleRec(rect, color);
    }

    // Drawing
    DrawRectangleRec(btnBounds, GRAY);

    EndDrawing();

    tick_accumulator -= tick_interval;
  }

  CloseWindow();
}
