#include <raylib.h>

const float window_heigt = 500;
const float window_width = 1000;

typedef struct {
  Rectangle user_paddle;
  float user_paddle_speed;
  Vector2 user_paddle_direction;
  Rectangle ai_paddle;
  float ai_paddle_speed;
  Vector2 ai_paddle_direction;
  Rectangle ball;
  float ball_speed;
  Vector2 ball_direction;
} Game;

void init_game(Game *game) {
  // init user_paddle
  game->user_paddle.x = 10;
  game->user_paddle.y = 10;
  game->user_paddle.width = 20;
  game->user_paddle.height = 100;
  game->user_paddle_speed = 3;
  game->user_paddle_direction = (Vector2){0, 0};
  // init ai paddle
  game->ai_paddle.width = 20;
  game->ai_paddle.height = 100;
  game->ai_paddle.x = window_width - 10 - game->ai_paddle.width;
  game->ai_paddle.y = 10;
  game->ai_paddle_speed = 3;
  game->ai_paddle_direction = (Vector2){0, 0};
  // init ball
  game->ball.height = 30;
  game->ball.width = 30;
  game->ball.x = window_width / 2 - game->ball.width / 2;
  game->ball.y = window_heigt / 2 - game->ball.height / 2;
}

void process_game_input() {}

void draw_game(Game *game) {
  // draw paddles
  DrawRectangleRec(game->user_paddle, BLUE);
  DrawRectangleRec(game->ai_paddle, RED);
  // draw ball
  DrawRectangleRec(game->ball, GREEN);
}

int main() {
  InitWindow(window_width, window_heigt, "Pong");
  Game game = {0};
  init_game(&game);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    process_game_input();
    draw_game(&game);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
