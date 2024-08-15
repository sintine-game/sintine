#include <stdbool.h>
#include <stdio.h>
#include "client.h"
#include "crosshair.h"
#include "game.h"
#include "raylib.h"
#include "sea.h"
#include "ship.h"
#include "style.h"

static Vector2 seaSelfPosition = {SCREEN_WIDTH / 2.0 - 20 - SEA_GRID_WIDTH * GRID_CELL_SIZE_PX,
                                  SCREEN_HEIGHT / 2.0 - SEA_GRID_HEIGHT* GRID_CELL_SIZE_PX / 2.0};
static Vector2 seaOpponentPosition = {SCREEN_WIDTH / 2.0 + 20,
                                      SCREEN_HEIGHT / 2.0 - SEA_GRID_HEIGHT* GRID_CELL_SIZE_PX / 2.0};

static Crosshair crosshair = {0};
static Sea seaSelf = {0};
static Sea seaOpponent = {0};

void InitPlayScreen(void) {
    seaSelf = CreateSea(seaSelfPosition);
    seaOpponent = CreateSea(seaOpponentPosition);

    crosshair = CreateCrosshair();
}

void UpdatePlayScreen(void) {
    for (int i = 0; i < SHIP_COUNT; i++) {
        UpdateShip(&ships[i], &seaSelf);
    }
    UpdateCrosshair(&crosshair, &seaOpponent);

    if (IsMyTurn && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        GridPosition gridPosition = GetCrosshairGridPosition(crosshair, &seaOpponent);
        printf("gridPosition: %d, %d\n", gridPosition.x, gridPosition.y);
        if (seaOpponent.cells[gridPosition.x][gridPosition.y] == CELL_EMPTY) {
            seaOpponent.cells[gridPosition.x][gridPosition.y] = TryHit(gridPosition) ? CELL_HIT : CELL_MISS;
            IsMyTurn = false;
            crosshair.active = false;
        }
    }
    if (!IsMyTurn) {
        crosshair.active = false;
        GridPosition opponentHitPosition = GetHit();
        if (opponentHitPosition.x >= 0 && opponentHitPosition.y >= 0) {
            for (int i = 0; i < SHIP_COUNT; i++) {
                Rectangle shipRect = GetShipGlobalArea(ships[i], seaSelf.position);
                Vector2 hitPosition = {seaSelf.position.x + (float)opponentHitPosition.x * GRID_CELL_SIZE_PX,
                                       seaSelf.position.y + (float)opponentHitPosition.y * GRID_CELL_SIZE_PX};
                if (CheckCollisionPointRec(hitPosition, shipRect)) {
                    seaSelf.cells[opponentHitPosition.x][opponentHitPosition.y] = CELL_HIT;
                    break;
                } else {
                    seaSelf.cells[opponentHitPosition.x][opponentHitPosition.y] = CELL_MISS;
                }
            }
            IsMyTurn = true;
            crosshair.active = true;
        }
    }
}

void DrawPlayScreen(void) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BACKGROUND_COLOR);
    Vector2 pos = {20, 10};
    DrawTextEx(font, "DEPLOYMENT", pos, (float)font.baseSize * 3.0f, 4, WHITE);
    DrawText("Deploy your ships", 20, 70, 20, WHITE);
    DrawSea(&seaSelf);
    DrawSea(&seaOpponent);
    for (int i = 0; i < SHIP_COUNT; i++) {
        DrawShip(ships[i], seaSelf.position);
    }
    for (int i = 0; i < SEA_GRID_HEIGHT; i++) {
        for (int j = 0; j < SEA_GRID_WIDTH; j++) {
            if (seaSelf.cells[j][i] == CELL_HIT) {
                DrawRectangle((int)seaSelf.position.x + j * GRID_CELL_SIZE_PX, (int)seaSelf.position.y + i * GRID_CELL_SIZE_PX,
                              GRID_CELL_SIZE_PX, GRID_CELL_SIZE_PX, RED);
            } else if (seaSelf.cells[j][i] == CELL_MISS) {
                DrawRectangle((int)seaSelf.position.x + j * GRID_CELL_SIZE_PX, (int)seaSelf.position.y + i * GRID_CELL_SIZE_PX,
                              GRID_CELL_SIZE_PX, GRID_CELL_SIZE_PX, GRAY);
            }
        }
    }
    DrawCrosshair(crosshair);
}

void UnloadPlayScreen(void) { UnloadCrosshair(&crosshair); }

int FinishPlayScreen(void) { return 0; }
