#include <stdbool.h>
#include <string.h>
#include "client.h"
#include "game.h"
#include "raylib.h"

static char roomId[16] = {0};
static int finishScreen = 0;

void InitJoinRoomScreen(void) {
    IsMyTurn = false;
}

void UpdateJoinRoomScreen(void) {
    if (IsKeyPressed(KEY_BACKSPACE)) {
        unsigned long len = strlen(roomId);
        if (len > 0) {
            roomId[len - 1] = '\0';
        }
    } else if (IsKeyPressed(KEY_ENTER)) {
        JoinRoom(roomId);

        finishScreen = 1;
    } else {
        unsigned long len = strlen(roomId);
        if (len < 15) {
            int key = GetCharPressed();
            if (key != 0 && (key >= '0' && key <= '9') || (key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) {
                roomId[len] = (char)key;
            }
        }
    }
}

void DrawJoinRoomScreen(void) {
    Color backgroundColor = {32, 30, 67, 255};

    ClearBackground(backgroundColor);
    DrawText("Join Room", 20, 20, 40, RAYWHITE);
    DrawText("Enter room ID", 20, 60, 20, RAYWHITE);
    DrawText(roomId, (int)SCREEN_CENTER.x - MeasureText(roomId, 20) / 2, (int)SCREEN_CENTER.y, 20, RAYWHITE);
}

void UnloadJoinRoomScreen(void) {}

int FinishJoinRoomScreen(void) { return finishScreen; }
