#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const float window_heigt = 500;
const float window_width = 1000;
const float speed = 5;
const int max = 46;
const int min = -45;

typedef struct {
  Rectangle user_paddle;
  float user_paddle_speed;
  Rectangle ai_paddle;
  float ai_paddle_speed;
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
  game->user_paddle_speed = speed;
  // init ai paddle
  game->ai_paddle.width = 20;
  game->ai_paddle.height = 100;
  game->ai_paddle.x = window_width - 10 - game->ai_paddle.width;
  game->ai_paddle.y = 10;
  game->ai_paddle_speed = speed;
  // init ball
  game->ball.height = 30;
  game->ball.width = 30;
  game->ball.x = window_width / 2 - game->ball.width / 2;
  game->ball.y = window_heigt / 2 - game->ball.height / 2;
  int angle = rand() % (max - min + 1) + min;
  double radians = angle * (PI / 180.0);
  game->ball_direction.x = cos(radians);
  game->ball_direction.y = sin(radians);
}

void process_game_input(Game *game) {
  if (IsKeyDown(KEY_UP)) {
    game->user_paddle.y -= speed;
  }
  if (IsKeyDown(KEY_DOWN)) {
    game->user_paddle.y += speed;
  }
  if (game->user_paddle.y <= 0) {
    game->user_paddle.y = 0;
  } else if (game->user_paddle.y >= window_heigt - game->user_paddle.height) {
    game->user_paddle.y = window_heigt - game->user_paddle.height;
  }
  game->ball.y += speed * game->ball_direction.y;
  game->ball.x += speed * game->ball_direction.x;
  if (CheckCollisionRecs(game->ball, game->user_paddle) ||
      CheckCollisionRecs(game->ball, game->ai_paddle)) {
    game->ball_direction.x *= -1;
  }
  if ((game->ball.y <= 0) ||
      (game->ball.y >= window_heigt - game->ball.height)) {
    game->ball_direction.y *= -1;
  }
  if ((game->ball.x <= 0) ||
      (game->ball.x >= window_width - game->ball.width)) {
    init_game(game);
  }
  // move ai paddle
  if (game->ball_direction.y < 0) {
    game->ai_paddle.y -= speed;
  } else {
    game->ai_paddle.y += speed;
  }
  if (game->ai_paddle.y <= 0) {
    game->ai_paddle.y = 0;
  } else if (game->ai_paddle.y >= window_heigt - game->ai_paddle.height) {
    game->ai_paddle.y = window_heigt - game->ai_paddle.height;
  }
}

void draw_game(Game *game) {
  // draw paddles
  DrawRectangleRec(game->user_paddle, BLUE);
  DrawRectangleRec(game->ai_paddle, RED);
  // draw ball
  DrawRectangleRec(game->ball, GREEN);
  char info[256];
  sprintf(info, "Direction X: %f\nDirection Y: %f", game->ball_direction.x,
          game->ball_direction.y);
  DrawText(info, 20, 20, 5, RED);
}

int main() {
  srand((unsigned int)(time(NULL)));
  InitWindow(window_width, window_heigt, "Pong");
  SetTargetFPS(60);
  Game game = {0};
  init_game(&game);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    process_game_input(&game);
    draw_game(&game);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
