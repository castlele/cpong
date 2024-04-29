#include <stdio.h>

#include "ball.h"
#include "game.h"
#include "player.h"
#include "raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Pong"
#define TARGET_FPS 120

#define BG_COLOR BLACK
#define FONT_SIZE 30

#define MAX_SCORE 25

#define DEBUG

// Private API

void drawFPSIfNeeded() {
#ifdef DEBUG
    char fps[20];
    sprintf(fps, "%d FPS", GetFPS());

    DrawText(fps, 0, 0, FONT_SIZE, WHITE);
#endif
}

void drawScore(Player *player, PlayerType side) {
    char score[MAX_SCORE + 1];
    Vector2 pos = { .y = 0 };

    sprintf(score, "%d", player->currentScore);

    int textSize = MeasureText(score, FONT_SIZE);

    switch (side) {
        case PLAYER_TYPE_LEFT:
            // Center of the left half of the screen
            pos.x = (GetScreenWidth() - 2*textSize) / 4.0;
            break;
        case PLAYER_TYPE_RIGHT:
            // Center of the right half of the screen
            pos.x = (3*GetScreenWidth() - 2*textSize) / 4.0;
            break;
    }

    DrawText(score, pos.x, pos.y, FONT_SIZE, WHITE);
}

// Public API

// TODO: Apply y velocity to the ball with player kick
// TODO: Apply acceleration
// TODO: Randomize default y velocity for ball
// TODO: Refactor runGame to be only the place with init, update and draw methods
// TODO: Increase speed of the ball with time
// TODO: Add AI for secong player
// TODO: Add controllers support
int runGame() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    SetTargetFPS(TARGET_FPS);

    Vector2 initialBallVelocity = { 1, 1 };
    Ball ball = initBall(initialBallVelocity);
    Player lPlayer = initPlayer(PLAYER_TYPE_LEFT);
    Player rPlayer = initPlayer(PLAYER_TYPE_RIGHT);
    float dt;

    while (!WindowShouldClose()) {
        dt = GetFrameTime();

        BeginDrawing();

        ClearBackground(BG_COLOR);

        drawFPSIfNeeded();

        kickTheBall(&lPlayer, &ball);
        kickTheBall(&rPlayer, &ball);

        if (isTouchingWall(&ball, WALL_LEFT)) {
            rPlayer.currentScore += 1;
            resetBallPosition(&ball);
        }

        if (isTouchingWall(&ball, WALL_RIGHT)) {
            lPlayer.currentScore += 1;
            resetBallPosition(&ball);
        }

        drawScore(&lPlayer, PLAYER_TYPE_LEFT);
        drawScore(&rPlayer, PLAYER_TYPE_RIGHT);

        updateBall(&ball, dt);

        updatePlayer(&lPlayer, dt);
        updatePlayer(&rPlayer, dt);

        drawBall(&ball);

        drawPlayer(&lPlayer);
        drawPlayer(&rPlayer);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
