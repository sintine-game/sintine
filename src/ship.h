#include <stdio.h>
#include "raylib.h"
#include "screens.h"
#include "sea.h"

#ifndef SHIP_H
#define SHIP_H

typedef enum Rotation { ROTATION_0 = 0, ROTATION_90, ROTATION_180, ROTATION_270 } Rotation;

typedef enum ShipType { SHIP_SMALL = 1, SHIP_MEDIUM, SHIP_LARGE } ShipType;

typedef struct Ship {
    Texture2D texture;
    ShipType type;
    Rotation rotation;
    GridPosition position;
    bool alive;
    bool isDeployed;
    bool isDragging;
} Ship;

Ship CreateShip(ShipType type, Rotation rotation, GridPosition position);
void UpdateShip(Ship* ship, Sea* sea);
void DrawShip(Ship ship, Vector2 offset);
void RandomizeShipPositions(Ship ships[], int count);
Rectangle GetShipGlobalArea(Ship ship, Vector2 offset);
void UnloadShip(Ship* ship);

#endif
