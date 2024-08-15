#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "button.h"
#include "client.h"
#include "game.h"
#include "raylib.h"
#include "screens.h"
#include "style.h"

enum { ROOM_NAME_LENGTH = 6 };

static int finishScreen = 0;
Button copyButton = {0};
char roomId[64] = {0};

void DrawCopyToClipboardButton(void);
char* GetRandomroomId(void);

void InitCreateRoomScreen(void) {
    IsMyTurn = true;
    strcpy(roomId, GetRandomroomId());
    Vector2 copyButtonPosition = {SCREEN_CENTER.x, SCREEN_CENTER.y + 100};
    copyButton = CreateButton(copyButtonPosition, BUTTON_COLOR, BUTTON_COLOR_HOVER, TEXT_COLOR, TEXT_COLOR_HOVER,
                              "COPY TO CLIPBOARD", 0);

    if (CreateRoom(roomId) < 0) {
        fprintf(stderr, "Failed to create room\n");
        exit(EXIT_FAILURE);
    }
}

void UpdateCreateRoomScreen(void) {
    if (IsKeyPressed(KEY_ENTER)) {
        finishScreen = 1;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), copyButton.rect)) {
        SetClipboardText(roomId);
        copyButton.text = "COPIED!";
    }
}

void DrawCreateRoomScreen(void) {
    Color backgroundColor = {32, 30, 67, 255};
    ClearBackground(backgroundColor);

    DrawText("Create Room", 20, 20, 40, RAYWHITE);
    DrawText("Press [ENTER] to start deployment", 20, 60, 20, RAYWHITE);

    char message[64] = {0};
    sprintf(message, "Room name: %s", roomId);
    DrawText(message, (int)(SCREEN_CENTER.x - (float)MeasureText(message, 20) / 2), (int)SCREEN_CENTER.y, 20, RAYWHITE);
    DrawButton(copyButton);
}

void UnloadCreateRoomScreen(void) {}

int FinishCreateRoomScreen(void) { return finishScreen; }

void DrawCopyToClipboardButton(void) {
    const char* text = "COPY TO CLIPBOARD";
    Rectangle button = {SCREEN_CENTER.x - (float)MeasureText(text, 20) / 2, SCREEN_CENTER.y + 100,
                        (float)MeasureText(text, 20) + 20, 50};
    button.y = (float)GetScreenHeight() - 100;
    Color buttonColor = {19, 75, 112, 255};
    Color buttonColorHover = {19, 95, 132, 255};
    Color textColor = {200, 200, 200, 255};

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){button.x, button.y, button.width, button.height})) {
        DrawRectangleRec(button, buttonColor);
        DrawText(text, (int)(button.x + 10), (int)(button.y + 15), 20, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            finishScreen = 1;
        }
    } else {
        DrawRectangleRec(button, buttonColorHover);
        DrawText(text, (int)(button.x + 10), (int)(button.y + 15), 20, textColor);
    }
}

char* GetRandomroomId(void) {
    static char roomId[ROOM_NAME_LENGTH] = {0};
    const char* characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    srand(time(NULL));
    for (int i = 0; i < ROOM_NAME_LENGTH; i++) {
        roomId[i] = characters[rand() % strlen(characters)];
    }

    return roomId;
}
