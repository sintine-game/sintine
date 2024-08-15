#include "game.h"
#include <stdbool.h>
#include "raylib.h"
#include "screens.h"

GameScreen currentScreen = WELCOME;
Font font = {0};
Ship ships[SHIP_COUNT] = {0};
bool IsMyTurn = false;

static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static GameScreen transToScreen = UNKNOWN;

static void ChangeToScreen(int screen);

static void TransitionToScreen(int screen);
static void UpdateTransition(void);
static void DrawTransition(void);

static void UpdateDrawFrame(void);

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "sintine");

    font = LoadFont("resources/mecha.png");

    currentScreen = WELCOME;
    InitWelcomeScreen();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }

    switch (currentScreen) {
        case JOIN_ROOM: UnloadJoinRoomScreen(); break;
        case CREATE_ROOM: UnloadCreateRoomScreen(); break;
        case DEPLOYMENT: UnloadDeployScreen(); break;
        default: break;
    }

    UnloadFont(font);

    CloseWindow();

    return 0;
}

static void ChangeToScreen(GameScreen screen) {
    switch (currentScreen) {
        case JOIN_ROOM: UnloadJoinRoomScreen(); break;
        case CREATE_ROOM: UnloadCreateRoomScreen(); break;
        case DEPLOYMENT: UnloadDeployScreen(); break;
        case PLAY: UnloadPlayScreen(); break;
        default: break;
    }

    switch (screen) {
        case WELCOME: InitWelcomeScreen(); break;
        case JOIN_ROOM: InitJoinRoomScreen(); break;
        case CREATE_ROOM: InitCreateRoomScreen(); break;
        case DEPLOYMENT: InitDeployScreen(); break;
        case PLAY: InitPlayScreen(); break;
        default: break;
    }

    currentScreen = screen;
}

static void TransitionToScreen(GameScreen screen) {
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

static void UpdateTransition(void) {
    if (!transFadeOut) {
        transAlpha += 0.05f;

        if (transAlpha > 1.01f) {
            transAlpha = 1.0f;

            switch (transFromScreen) {
                case JOIN_ROOM: UnloadJoinRoomScreen(); break;
                case CREATE_ROOM: UnloadCreateRoomScreen(); break;
                case DEPLOYMENT: UnloadDeployScreen(); break;
                case PLAY: UnloadPlayScreen(); break;
                default: break;
            }

            switch (transToScreen) {
                case JOIN_ROOM: InitJoinRoomScreen(); break;
                case CREATE_ROOM: InitCreateRoomScreen(); break;
                case DEPLOYMENT: InitDeployScreen(); break;
                case PLAY: InitPlayScreen(); break;
                default: break;
            }

            currentScreen = transToScreen;

            transFadeOut = true;
        }
    } else {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f) {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = UNKNOWN;
        }
    }
}

static void DrawTransition(void) { DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha)); }

static void UpdateDrawFrame(void) {
    if (!onTransition) {
        switch (currentScreen) {
            case WELCOME: {
                UpdateWelcomeScreen();

                if (FinishWelcomeScreen() == JOIN_ROOM) {
                    TransitionToScreen(JOIN_ROOM);
                } else if (FinishWelcomeScreen() == CREATE_ROOM) {
                    TransitionToScreen(CREATE_ROOM);
                }
            } break;
            case JOIN_ROOM: {
                UpdateJoinRoomScreen();

                if (FinishJoinRoomScreen() == 1) {
                    TransitionToScreen(DEPLOYMENT);
                }
            } break;
            case CREATE_ROOM: {
                UpdateCreateRoomScreen();

                if (FinishCreateRoomScreen() == 1) {
                    TransitionToScreen(WAIT_ROOM);
                }
            } break;
            case WAIT_ROOM: {
                UpdateWaitRoomScreen();

                if (FinishWaitRoomScreen() == 1) {
                    TransitionToScreen(DEPLOYMENT);
                }
            } break;
            case DEPLOYMENT: {
                UpdateDeployScreen();

                if (FinishDeployScreen() == 1) {
                    TransitionToScreen(WAIT_DEPLOY);
                }
            } break;
            case WAIT_DEPLOY: {
                UpdateWaitDeployScreen();

                if (FinishWaitDeployScreen() == 1) {
                    TransitionToScreen(PLAY);
                }
            } break;
            case PLAY: {
                UpdatePlayScreen();
            } break;
            default: break;
        }
    } else {
        UpdateTransition();
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    switch (currentScreen) {
        case WELCOME: DrawWelcomeScreen(); break;
        case JOIN_ROOM: DrawJoinRoomScreen(); break;
        case CREATE_ROOM: DrawCreateRoomScreen(); break;
        case WAIT_ROOM: DrawWaitRoomScreen(); break;
        case DEPLOYMENT: DrawDeployScreen(); break;
        case WAIT_DEPLOY: DrawWaitDeployScreen(); break;
        case PLAY: DrawPlayScreen(); break;
        default: break;
    }

    if (onTransition) {
        DrawTransition();
    }

    EndDrawing();
}
