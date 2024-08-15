#include "raylib.h"

#ifndef SEA_H
#define SEA_H

#define GRID_CELL_SIZE_PX 40
#define SEA_GRID_WIDTH    10
#define SEA_GRID_HEIGHT   10

typedef struct GridPosition {
    int x;
    int y;
} GridPosition;

typedef enum CellType { CELL_EMPTY = 0, CELL_SHIP, CELL_HIT, CELL_MISS } CellType;

typedef struct Sea {
    Vector2 position;
    CellType cells[SEA_GRID_WIDTH][SEA_GRID_HEIGHT];
} Sea;

Sea CreateSea(Vector2 position);
void DrawSea(Sea* sea);
Rectangle GetSeaRectangle(Sea* sea);

#endif
