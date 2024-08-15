#include "crosshair.h"
#include <stdbool.h>
#include "raylib.h"

Crosshair CreateCrosshair() {
    Crosshair crosshair = {0};
    crosshair.textureActive = LoadTexture("resources/sprites/crosshair/crosshair_active.png");
    crosshair.textureDisabled = LoadTexture("resources/sprites/crosshair/crosshair_disabled.png");
    crosshair.position = (Vector2){0};
    crosshair.active = true;

    return crosshair;
}

void UpdateCrosshair(Crosshair* crosshair, Sea* sea) {
    Vector2 mousePosition = GetMousePosition();

    int gridX = (int)((mousePosition.x - sea->position.x) / GRID_CELL_SIZE_PX);
    int gridY = (int)((mousePosition.y - sea->position.y) / GRID_CELL_SIZE_PX);

    if (gridX >= 0 && gridX < SEA_GRID_WIDTH && gridY >= 0 && gridY < SEA_GRID_HEIGHT) {
        crosshair->active = true;
        crosshair->position.x = sea->position.x + (float)gridX * GRID_CELL_SIZE_PX + (float)GRID_CELL_SIZE_PX / 2;
        crosshair->position.y = sea->position.y + (float)gridY * GRID_CELL_SIZE_PX + (float)GRID_CELL_SIZE_PX / 2;
    } else {
        crosshair->active = false;
    }
}

void DrawCrosshair(Crosshair crosshair) {
    Rectangle sourceRect = {0, 0, (float)crosshair.textureActive.width, (float)crosshair.textureActive.height};
    Rectangle destRect = {crosshair.position.x, crosshair.position.y, GRID_CELL_SIZE_PX + 5, GRID_CELL_SIZE_PX + 5};
    Vector2 origin = {destRect.width / 2, destRect.height / 2};
    if (crosshair.active) {
        DrawTexturePro(crosshair.textureActive, sourceRect, destRect, origin, 0.0f, WHITE);
    } else {
        DrawTexturePro(crosshair.textureDisabled, sourceRect, destRect, origin, 0.0f, WHITE);
    }
}

GridPosition GetCrosshairGridPosition(Crosshair crosshair, Sea* sea) {
    GridPosition gridPosition = {0};

    gridPosition.x = (int)((crosshair.position.x - sea->position.x) / GRID_CELL_SIZE_PX);
    gridPosition.y = (int)((crosshair.position.y - sea->position.y) / GRID_CELL_SIZE_PX);

    return gridPosition;
}

void UnloadCrosshair(Crosshair* crosshair) {
    UnloadTexture(crosshair->textureActive);
    UnloadTexture(crosshair->textureDisabled);
}
