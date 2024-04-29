#ifndef __BALL_H_
#define __BALL_H_

#include <stdbool.h>

#include "raylib.h"
#include "wall.h"

typedef struct {
    int centerX;
    int centerY;
    float radius;
    Color color;
    int speed;
    Vector2 currentVelocity;
} Ball;

bool isTouchingWall(Ball *ball, Wall wall);
void resetBallPosition(Ball *ball);

Ball initBall(Vector2 velocity);
void updateBall(Ball *ball, float dt);
void drawBall(Ball *ball);

#endif // __BALL_H_
