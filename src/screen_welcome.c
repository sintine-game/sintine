#include "button.h"
#include "client.h"
#include "game.h"
#include "raylib.h"
#include "screens.h"
#include "ship.h"
#include "style.h"

GameScreen selectedScreen = UNKNOWN;
Button joinButton = {0};
Button createButton = {0};

void InitWelcomeScreen(void) {
    joinButton = CreateButton((Vector2){(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 - 100}, BUTTON_COLOR,
                              BUTTON_COLOR_HOVER, TEXT_COLOR, TEXT_COLOR_HOVER, "Join Room", 200);
    createButton = CreateButton((Vector2){(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 + 100},
                                BUTTON_COLOR, BUTTON_COLOR_HOVER, TEXT_COLOR, TEXT_COLOR_HOVER, "Create Room", 200);
    InitClient();
    selectedScreen = UNKNOWN;
}

void UpdateWelcomeScreen(void) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        const Vector2 center = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};

        if (IsButtonPressed(joinButton)) {
            selectedScreen = JOIN_ROOM;
        } else if (IsButtonPressed(createButton)) {
            selectedScreen = CREATE_ROOM;
        }
    }
}

void DrawWelcomeScreen(void) {
    ClearBackground(BACKGROUND_COLOR);

    DrawButton(joinButton);
    DrawButton(createButton);
}

GameScreen FinishWelcomeScreen(void) { return selectedScreen; }
