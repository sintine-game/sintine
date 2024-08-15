#include "raylib.h"

#ifndef BUTTON_H
#define BUTTON_H

typedef struct Button {
    Rectangle rect;
    Color color;
    Color colorHover;
    Color textColor;
    Color textColorHover;
    char* text;
} Button;

Button CreateButton(Vector2 position, Color color, Color colorHover, Color textColor, Color textColorHover, char* text,
                    int minWidth);
void DrawButton(Button button);
bool IsButtonPressed(Button button);

#endif
