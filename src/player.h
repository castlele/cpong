#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "ball.h"
#include "raylib.h"

typedef struct {
    Rectangle body;
    int speed;
    Color color;
    int upKey;
    int downKey;
    int currentScore;
} Player;

typedef enum {
    PLAYER_TYPE_LEFT,
    PLAYER_TYPE_RIGHT,
} PlayerType;

void kickTheBall(Player *player, Ball *ball);

Player initPlayer(PlayerType type);
void updatePlayer(Player *player, float dt);
void drawPlayer(Player *player);

#endif // __PLAYER_H_
