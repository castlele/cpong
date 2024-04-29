#include <stddef.h>

#include "ball.h"
#include "utils.h"

#define CENTER_X GetScreenWidth() / 2
#define CENTER_Y GetScreenHeight() / 2
#define DEFAULT_RADIUS 20
#define DEFAULT_SPEED 300
#define DEFAULT_COLOR WHITE

// Private API

bool isTouchingWalls(Ball *ball, Wall walls[], size_t len) {
    bool touching = false;

    for (int i = 0; i < len; ++i) {
        touching = touching || isTouchingWall(ball, walls[i]);
    }

    return touching;
}

// Public API

bool isTouchingWall(Ball *ball, Wall wall) {
    bool touching = false;

    int minX = ball->centerX - ball->radius;
    int maxX = ball->centerX + ball->radius;
    int minY = ball->centerY - ball->radius;
    int maxY = ball->centerY + ball->radius;

    switch (wall) {
        case WALL_TOP:
            touching = minY <= 0;
            break;
        case WALL_BOTTOM:
            touching = maxY >= GetScreenHeight();
            break;
        case WALL_LEFT:
            touching = minX <= 0;
            break;
        case WALL_RIGHT:
            touching = maxX >= GetScreenWidth();
            break;
    }

    return touching;
}

void resetBallPosition(Ball *ball) {
    ball->centerX = CENTER_X;
    ball->centerY = CENTER_Y;

    ball->currentVelocity.x *= -1;
    ball->currentVelocity.y = 0;
}

Ball initBall(Vector2 velocity) {
    Ball b = {
        .centerX = CENTER_X,
        .centerY = CENTER_Y,
        .currentVelocity = velocity,
        .radius = DEFAULT_RADIUS,
        .speed = DEFAULT_SPEED,
        .color = DEFAULT_COLOR,
    };

    return b;
}

void updateBall(Ball *ball, float dt) {
    Wall topBottomWalls[] = { WALL_TOP , WALL_BOTTOM };
    Wall leftRightWalls[] = { WALL_LEFT, WALL_RIGHT };

    if (isTouchingWalls(ball, leftRightWalls, LEN(leftRightWalls))) {
        ball->currentVelocity.x *= -1;
    }

    if (isTouchingWalls(ball, topBottomWalls, LEN(topBottomWalls))) {
        ball->currentVelocity.y *= -1;
    }

    float xs = (float)(ball->speed * ball->currentVelocity.x) * dt;
    float ys = (float)(ball->speed * ball->currentVelocity.y) * dt;

    ball->centerX += xs;
    ball->centerY += ys;
}

void drawBall(Ball *ball) {
    DrawCircle(ball->centerX, ball->centerY, ball->radius, ball->color);
}
