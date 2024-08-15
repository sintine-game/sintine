#include "button.h"
#include <stdbool.h>
#include "raylib.h"

const int PADDING_X = 10;
const int PADDING_Y = 10;
const int FONT_SIZE = 20;

Button CreateButton(Vector2 centerPosition, Color color, Color colorHover, Color textColor, Color textColorHover,
                    char* text, int minWidth) {
    Button button = {0};
    const int textWidth = MeasureText(text, FONT_SIZE);
    int rectWidth = textWidth + PADDING_X * 2;
    if (minWidth != 0 && rectWidth < minWidth) {
        rectWidth = minWidth;
    }

    centerPosition.x -= (float)rectWidth / 2.0f;
    centerPosition.y -= (float)(FONT_SIZE + PADDING_Y * 2) / 2;

    button.rect =
        (Rectangle){centerPosition.x, centerPosition.y, (float)rectWidth, (float)FONT_SIZE + (float)PADDING_Y * 2};
    button.color = color;
    button.colorHover = colorHover;
    button.textColor = textColor;
    button.textColorHover = textColorHover;
    button.text = text;

    return button;
}

void DrawButton(Button button) {
    if (CheckCollisionPointRec(GetMousePosition(), button.rect)) {
        DrawRectangleRec(button.rect, button.colorHover);
        DrawText(button.text, (int)button.rect.x + PADDING_X, (int)button.rect.y + PADDING_Y, FONT_SIZE,
                 button.textColorHover);
    } else {
        DrawRectangleRec(button.rect, button.color);
        DrawText(button.text, (int)button.rect.x + PADDING_X, (int)button.rect.y + PADDING_Y, FONT_SIZE,
                 button.textColor);
    }
}

bool IsButtonPressed(Button button) {
    return CheckCollisionPointRec(GetMousePosition(), button.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
