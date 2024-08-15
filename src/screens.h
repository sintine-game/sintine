#include "raylib.h"

#ifndef SCREENS_H
#define SCREENS_H

typedef enum GameScreen {
    UNKNOWN = -1,
    WELCOME = 0,
    JOIN_ROOM,
    CREATE_ROOM,
    WAIT_ROOM,
    DEPLOYMENT,
    WAIT_DEPLOY,
    PLAY,
} GameScreen;

extern GameScreen currentScreen;
extern Font font;

void InitWelcomeScreen(void);
void UpdateWelcomeScreen(void);
void DrawWelcomeScreen(void);
GameScreen FinishWelcomeScreen(void);

void InitJoinRoomScreen(void);
void UpdateJoinRoomScreen(void);
void DrawJoinRoomScreen(void);
void UnloadJoinRoomScreen(void);
int FinishJoinRoomScreen(void);

void InitCreateRoomScreen(void);
void UpdateCreateRoomScreen(void);
void DrawCreateRoomScreen(void);
void UnloadCreateRoomScreen(void);
int FinishCreateRoomScreen(void);

void DrawWaitRoomScreen(void);
void UpdateWaitRoomScreen(void);
int FinishWaitRoomScreen(void);

void DrawWaitDeployScreen(void);
void UpdateWaitDeployScreen(void);
int FinishWaitDeployScreen(void);

void InitPlayScreen(void);
void UpdatePlayScreen(void);
void DrawPlayScreen(void);
void UnloadPlayScreen(void);
int FinishPlayScreen(void);

void InitDeployScreen(void);
void UpdateDeployScreen(void);
void DrawDeployScreen(void);
void UnloadDeployScreen(void);
int FinishDeployScreen(void);

#endif
