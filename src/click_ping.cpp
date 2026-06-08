#include <print>

#include "raylib.h"

auto renderClickPing() -> void {
  InitWindow(500, 500, "Click Ping");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    Rectangle btnBounds = {.x = 100, .y = 100, .width = 200, .height = 50};

    if (CheckCollisionPointRec(GetMousePosition(), btnBounds)) {
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        std::println("INFO: Button Clicked");
      }
    }

    // Drawing
    DrawRectangleRec(btnBounds, GRAY);
    DrawText("CLICK ME", 120, 115, 20, BLACK);

    EndDrawing();
  }

  CloseWindow();
}
