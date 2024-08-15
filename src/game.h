#include "raylib.h"
#include "sea.h"
#include "ship.h"

#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 900
#define SPRITE_SCALE  GRID_CELL_SIZE_PX / 10.0f
#define SHIP_COUNT    4

static const Vector2 SCREEN_CENTER = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

extern Ship ships[SHIP_COUNT];
extern bool IsMyTurn;

#endif
