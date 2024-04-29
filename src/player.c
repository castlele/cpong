#include "player.h"

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 50
#define ZERO_SCORE 0

#define DEFAULT_SPEED 300

// Private API

void moveUp(Player *player, float dt) {
    player->body.y -= (float)player->speed * dt;

    if (player->body.y < 0) player->body.y = 0;
}

void moveDown(Player *player, float dt) {
    player->body.y += (float)player->speed * dt;

    int sh = GetScreenHeight();
    int maxY = player->body.y + player->body.height;

    if (maxY > sh) player->body.y = sh - player->body.height;
}

// Public API

void kickTheBall(Player *player, Ball *ball) {
    Vector2 ballPos = { ball->centerX, ball->centerY };

    if (CheckCollisionCircleRec(ballPos, ball->radius, player->body)) {
        ball->currentVelocity.x *= -1;
    }
}

Player initPlayer(PlayerType type) {
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();

    Rectangle body;
    Player p = {
        .color = WHITE,
        .speed = DEFAULT_SPEED,
        .currentScore = ZERO_SCORE,
    };

    body.width = PLAYER_WIDTH;
    body.height = PLAYER_HEIGHT;

    body.y = (screenHeight - body.height) / 2;

    switch (type) {
        case PLAYER_TYPE_LEFT:
            body.x = 0;
            p.upKey = KEY_W;
            p.downKey = KEY_S;
            break;

        case PLAYER_TYPE_RIGHT:;
            body.x = screenWidth - body.width;
            p.upKey = KEY_UP;
            p.downKey = KEY_DOWN;
            break;
    }

    p.body = body;

    return p;
}

void updatePlayer(Player *player, float dt) {
    if (IsKeyDown(player->upKey)) {
        moveUp(player, dt);
    } else if (IsKeyDown(player->downKey)) {
        moveDown(player, dt);
    }
}

void drawPlayer(Player *player) {
    Rectangle body = player->body;

    DrawRectangle(body.x, body.y, body.width, body.height, player->color);
}
