#include "ship.h"
#include <raylib.h>
#include <stdbool.h>
#include "game.h"
#include "sea.h"

Ship CreateShip(ShipType type, Rotation rotation, GridPosition position) {
    Ship ship = {0};
    ship.type = type;
    ship.rotation = rotation;
    ship.position = position;
    ship.alive = true;

    switch (type) {
        case SHIP_SMALL: {
            ship.texture = LoadTexture("resources/sprites/ships/ship_small.png");
        } break;
        case SHIP_MEDIUM: {
            ship.texture = LoadTexture("resources/sprites/ships/ship_medium.png");
        } break;
        case SHIP_LARGE: {
            ship.texture = LoadTexture("resources/sprites/ships/ship_large.png");
        } break;
        default: break;
    }

    return ship;
}

Rectangle GetShipGlobalArea(Ship ship, Vector2 offset) {
    Rectangle area = {0, 0, 0, 0};
    int size = (int)ship.type * GRID_CELL_SIZE_PX;

    area.x = (float)ship.position.x * GRID_CELL_SIZE_PX + offset.x;
    area.y = (float)ship.position.y * GRID_CELL_SIZE_PX + offset.y;

    switch (ship.rotation) {
        case ROTATION_0:
        case ROTATION_180: {
            area.width = (float)size;
            area.height = GRID_CELL_SIZE_PX;
            if (ship.rotation == ROTATION_180) {
                area.x -= (float)size - GRID_CELL_SIZE_PX;
            }
        } break;
        case ROTATION_90:
        case ROTATION_270: {
            area.width = GRID_CELL_SIZE_PX;
            area.height = (float)size;
            if (ship.rotation == ROTATION_270) {
                area.y -= (float)size - GRID_CELL_SIZE_PX;
            }
        } break;
        default: break;
    }

    return area;
}

void DrawShip(Ship ship, Vector2 offset) {
    const Rectangle area = GetShipGlobalArea(ship, offset);

    float rotation = 0.0f;
    switch (ship.rotation) {
        case ROTATION_0: rotation = 0.0f; break;
        case ROTATION_90: rotation = 90.0f; break;
        case ROTATION_180: rotation = 180.0f; break;
        case ROTATION_270: rotation = 270.0f; break;
        default: break;
    }

    Rectangle sourceRect = {0, 0, (float)ship.texture.width, (float)ship.texture.height};

    Rectangle destRect = {area.x + area.width / 2.0f, area.y + area.height / 2.0f,
                          ship.rotation == ROTATION_90 || ship.rotation == ROTATION_270 ? area.height : area.width,
                          ship.rotation == ROTATION_90 || ship.rotation == ROTATION_270 ? area.width : area.height};

    Vector2 origin = {destRect.width / 2.0f, destRect.height / 2.0f};

    DrawTexturePro(ship.texture, sourceRect, destRect, origin, rotation, WHITE);
}

void RandomizeShipPositions(Ship ships[], int count) {
    for (int i = 0; i < count; i++) {
        ships[i].position.x = GetRandomValue(0, SEA_GRID_WIDTH - 1);
        ships[i].position.y = GetRandomValue(0, SEA_GRID_HEIGHT - 1);
        ships[i].rotation = (Rotation)GetRandomValue(0, 3);
    }
}

void UnloadShip(Ship* ship) { UnloadTexture(ship->texture); }

void UpdateShip(Ship* ship, Sea* sea) {
    if (ship->isDeployed) {
        return;
    }

    Vector2 mousePosition = GetMousePosition();

    Rectangle shipArea = GetShipGlobalArea(*ship, sea->position);

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && CheckCollisionPointRec(mousePosition, shipArea)) {
        ship->rotation = (Rotation)(((int)ship->rotation + 1) % 4);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePosition, shipArea)) {
        ship->isDragging = true;
    }

    if (ship->isDragging) {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            ship->isDragging = false;
        } else {
            Vector2 newMousePosition = GetMousePosition();

            ship->position.x = (unsigned int)((newMousePosition.x - sea->position.x) / GRID_CELL_SIZE_PX);
            ship->position.y = (unsigned int)((newMousePosition.y - sea->position.y) / GRID_CELL_SIZE_PX);
        }
    }
}
