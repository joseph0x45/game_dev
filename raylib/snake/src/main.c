#include "raylib.h"

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    /* ClearBackground(RAYWHITE); */
    DrawText("Congrats! You created your first window!", 190, 200, 20,
             LIGHTGRAY);
    DrawCircle(10, 10, 20, RED);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
