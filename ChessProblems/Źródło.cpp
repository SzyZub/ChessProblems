#include "raylib.h"

#define SCREEN_W 1200
#define SCREEN_H 900
#define FONTDEF SCREEN_H / 15

class drawCl {
public:
    drawCl() {
        Font GetFontDefault(void);
    }
    void drawMenu() {
        DrawRectangle(0, 0, SCREEN_W, SCREEN_H, BLACK);
        DrawRectangle(0, SCREEN_H/3 - 3, SCREEN_W, 6, WHITE);
        DrawRectangle(0, SCREEN_H * 2/ 3 - 3, SCREEN_W, 6, WHITE);
        DrawText("Knight's tour problem", (SCREEN_W - MeasureText("Knight's tour problem", FONTDEF))/2, (SCREEN_H/3-FONTDEF)/2, FONTDEF, WHITE);
        DrawText("N queen problem", (SCREEN_W - MeasureText("N queen problem", FONTDEF)) / 2, SCREEN_H/3 + (SCREEN_H / 3 - FONTDEF) / 2, FONTDEF, WHITE);
        DrawText("Exit", (SCREEN_W - MeasureText("Exit", FONTDEF)) / 2, SCREEN_H / 3 * 2 + (SCREEN_H / 3 - FONTDEF) / 2, FONTDEF, WHITE);
    }
};

void DrawText(const char* text, int posX, int posY, int fontSize, Color color);

int main(void)
{
    InitWindow(1200, 900, "Chess problems");
    SetTargetFPS(30);
    drawCl draw;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        draw.drawMenu();
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
