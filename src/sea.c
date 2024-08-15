#include "sea.h"
#include "raylib.h"
#include "style.h"

Sea CreateSea(Vector2 position) {
    Sea sea = {0};
    sea.position = position;
    for (int x = 0; x < SEA_GRID_WIDTH; x++) {
        for (int y = 0; y < SEA_GRID_HEIGHT; y++) {
            sea.cells[x][y] = CELL_EMPTY;
        }
    }

    return sea;
}

void DrawSea(Sea* sea) {
    for (int x = 0; x < SEA_GRID_WIDTH; x++) {
        for (int y = 0; y < SEA_GRID_HEIGHT; y++) {
            Rectangle cell = {sea->position.x + (float)x * GRID_CELL_SIZE_PX, sea->position.y + (float)y * GRID_CELL_SIZE_PX,
                              GRID_CELL_SIZE_PX, GRID_CELL_SIZE_PX};

            switch (sea->cells[x][y]) {
                case CELL_EMPTY:
                    DrawRectangleRec(cell, SEA_COLOR);
                    DrawRectangleLinesEx(cell, 1, BORDER_COLOR);
                    break;
                case CELL_SHIP:
                    DrawRectangleRec(cell, SEA_COLOR);
                    DrawRectangleLinesEx(cell, 1, RED);
                    break;
                case CELL_HIT:
                    DrawRectangleRec(cell, RED);
                    DrawRectangleLinesEx(cell, 1, BORDER_COLOR);
                    break;
                case CELL_MISS:
                    DrawRectangleRec(cell, GRAY);
                    DrawRectangleLinesEx(cell, 1, BORDER_COLOR);
                    break;
                default: break;
            }
        }
    }
}

Rectangle GetSeaRectangle(Sea* sea) {
    return (Rectangle){sea->position.x, sea->position.y, SEA_GRID_WIDTH * GRID_CELL_SIZE_PX, SEA_GRID_HEIGHT * GRID_CELL_SIZE_PX};
}
