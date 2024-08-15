#include <unistd.h>
#include "client.h"
#include "game.h"
#include "raylib.h"

static int finishScreen = 0;

void DrawWaitDeployScreen(void) {
    Color backgroundColor = {32, 30, 67, 255};
    ClearBackground(backgroundColor);

    const char* message = "Waiting for other player to deploy...";
    DrawText(message, (int)(SCREEN_CENTER.x - (float)MeasureText(message, 20) / 2), (int)SCREEN_CENTER.y, 20, RAYWHITE);
}

void UpdateWaitDeployScreen(void) {
    if (IsOpponentDeployed()) {
        finishScreen = 1;
    }
    sleep(1);
}

int FinishWaitDeployScreen(void) { return finishScreen; }
