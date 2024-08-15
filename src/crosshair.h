#include "raylib.h"
#include "sea.h"

#ifndef CROSSHAIR_H
#define CROSSHAIR_H

typedef struct Crosshair {
    Texture2D textureActive;
    Texture2D textureDisabled;
    Vector2 position;
    bool active;
} Crosshair;

Crosshair CreateCrosshair();
void UpdateCrosshair(Crosshair* crosshair, Sea* sea);
void DrawCrosshair(Crosshair crosshair);
GridPosition GetCrosshairGridPosition(Crosshair crosshair, Sea* sea);
void UnloadCrosshair(Crosshair* crosshair);

#endif
