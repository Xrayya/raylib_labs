#include <chrono>
#include <print>
#include <random>
#include <utility>
#include <vector>

#include "raylib.h"

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

auto clickSpawnRandomRectangle() -> void {
  std::vector<std::pair<Rectangle, Color>> rects;

  InitWindow(1000, 1000, "Click Random Rectangle");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);

    Rectangle btnBounds = {.x = 400, .y = 900, .width = 200, .height = 50};

    if (CheckCollisionPointRec(GetMousePosition(), btnBounds)) {
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        std::println("INFO: Button Clicked");
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
      }
    }

    for (const auto& [rect, color] : rects) {
      DrawRectangleRec(rect, color);
    }

    // Drawing
    DrawRectangleRec(btnBounds, GRAY);
    DrawText("CLICK ME", 420, 915, 20, BLACK);

    EndDrawing();
  }

  CloseWindow();
}
