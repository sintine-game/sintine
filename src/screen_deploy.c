#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "button.h"
#include "client.h"
#include "game.h"
#include "raylib.h"
#include "screens.h"
#include "sea.h"
#include "ship.h"
#include "style.h"

static int framesCounter = 0;
static int finishScreen = 0;

static bool dragging = false;
static int draggedShipIndex = -1;
static Vector2 dragOffset = {0, 0};

Button deployButton = {0};
Sea sea = {0};
Vector2 seaPosition = {SCREEN_WIDTH / 2.0 - SEA_GRID_WIDTH * GRID_CELL_SIZE_PX / 2.0,
                       SCREEN_HEIGHT / 2.0 - SEA_GRID_HEIGHT* GRID_CELL_SIZE_PX / 2.0};

void DrawBorders(Vector2 offset);
char* FleetCoordinates();

void InitDeployScreen(void) {
    sea = CreateSea(seaPosition);

    framesCounter = 0;
    finishScreen = 0;

    Vector2 deployButtonPosition = {SCREEN_CENTER.x, SCREEN_CENTER.y + 300};
    deployButton = CreateButton(deployButtonPosition, BUTTON_COLOR, BUTTON_COLOR_HOVER, TEXT_COLOR, TEXT_COLOR_HOVER,
                                "DEPLOY", 200);

    ships[0] = CreateShip(SHIP_SMALL, ROTATION_0, (GridPosition){0, 0});
    ships[1] = CreateShip(SHIP_MEDIUM, ROTATION_270, (GridPosition){0, 0});
    ships[3] = CreateShip(SHIP_MEDIUM, ROTATION_90, (GridPosition){0, 0});
    ships[2] = CreateShip(SHIP_LARGE, ROTATION_180, (GridPosition){0, 0});

    RandomizeShipPositions(ships, SHIP_COUNT);
}

void UpdateDeployScreen(void) {
    if (IsKeyPressed(KEY_ENTER)) {
        const char* fleet = FleetCoordinates();
        DeployFleet(fleet);
        finishScreen = 1;
    }

    for (int i = 0; i < SHIP_COUNT; i++) {
        UpdateShip(&ships[i], &sea);
    }

    if (IsButtonPressed(deployButton)) {
        const char* fleet = FleetCoordinates();
        printf("Fleet: %s\n", fleet);
        ssize_t result = DeployFleet(fleet);
        printf("DeployFleet: %ld\n", result);
        finishScreen = 1;
    }
}

void DrawDeployScreen(void) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BACKGROUND_COLOR);
    Vector2 pos = {20, 10};
    DrawTextEx(font, "DEPLOYMENT", pos, (float)font.baseSize * 3.0f, 4, WHITE);
    DrawText("Deploy your ships", 20, 70, 20, WHITE);

    Vector2 offset;
    const int centerX = GetScreenWidth() / 2;
    const int centerY = GetScreenHeight() / 2;
    offset.x = (float)centerX - ((float)(SEA_GRID_WIDTH * GRID_CELL_SIZE_PX) / 2);
    offset.y = (float)centerY - ((float)SEA_GRID_HEIGHT * GRID_CELL_SIZE_PX) / 2;

    DrawSea(&sea);

    for (int i = 0; i < SHIP_COUNT; i++) {
        DrawShip(ships[i], offset);
    }

    DrawButton(deployButton);
}

void UnloadDeployScreen(void) {}

int FinishDeployScreen(void) { return finishScreen; }

int IsCellOccupied(GridPosition position) {
    for (int i = 0; i < SHIP_COUNT; i++) {
        Ship ship = ships[i];
        Rectangle shipArea = {(float)ship.position.x, (float)ship.position.y, ship.type, 1};
        if (CheckCollisionPointRec((Vector2){(float)position.x, (float)position.y}, shipArea)) {
            return 1;
        }
    }

    return 0;
}

void DrawBorders(Vector2 offset) {
    Color borderColor = {39, 41, 45, 128};
    for (int x = 0; x < SEA_GRID_WIDTH; x++) {
        for (int y = 0; y < SEA_GRID_HEIGHT; y++) {
            DrawRectangleLines((int)offset.x + x * GRID_CELL_SIZE_PX, (int)offset.y + y * GRID_CELL_SIZE_PX,
                               GRID_CELL_SIZE_PX, GRID_CELL_SIZE_PX, borderColor);
        }
    }
}

char* FleetCoordinates() {
    static char buffer[32];
    buffer[0] = '\0';

    for (int i = 0; i < SEA_GRID_WIDTH; i++) {
        for (int j = 0; j < SEA_GRID_HEIGHT; j++) {
            GridPosition position = {i, j};
            if (IsCellOccupied(position)) {
                char temp[16];
                sprintf(temp, "%d,%d;", i, j);
                strcat(buffer, temp);
            }
        }
    }

    buffer[strlen(buffer) - 1] = '\0';

    return buffer;
}
