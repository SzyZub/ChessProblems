#include "raylib.h"
#include <iostream>

#define SCREEN_W 1200
#define SCREEN_H 900
#define FONTDEF SCREEN_H / 15

typedef struct StrMousePos {
    int x, y;
}StrMousePos;

typedef enum EnMenuFlags {
    EMainMenu = 0,
    EKnightMenu,
    EKnightAnswer
} EnMenuFlags;

class MenuLogic {
private:
    EnMenuFlags flag;
    int size, col, row;
public:
    MenuLogic() {
        size = 1;
        col = 1;
        row = 1;
        flag = EMainMenu;
        SetMouseCursor(4);
        Font GetFontDefault(void);
    }
    StrMousePos _getMousePos(){
        StrMousePos temp;
        temp.x = GetTouchX();
        temp.y = GetTouchY();
        return temp;
    }
    void _drawChoice() {
        BeginDrawing();
        switch (flag) {
        case EMainMenu:
            _drawMainMenu();
            break;
        case EKnightMenu:
            _drawKnightMenu();
            break;
        case EKnightAnswer:
            _drawKnightAnswer();
            break;
        }
        ClearBackground(BLACK);
        EndDrawing();
    }
    void _drawMainMenu() {
        for (int i = 1; i < 3; i++) {
            DrawRectangle(0, (SCREEN_H / 3 - 3) * i, SCREEN_W, 6, WHITE);
        }
        DrawText("Knight's tour problem", (SCREEN_W - MeasureText("Knight's tour problem", FONTDEF))/2, (SCREEN_H/3-FONTDEF)/2, FONTDEF, WHITE);
        DrawText("N queen problem", (SCREEN_W - MeasureText("N queen problem", FONTDEF)) / 2, SCREEN_H/3 + (SCREEN_H / 3 - FONTDEF) / 2, FONTDEF, WHITE);
        DrawText("Exit", (SCREEN_W - MeasureText("Exit", FONTDEF)) / 2, SCREEN_H / 3 * 2 + (SCREEN_H / 3 - FONTDEF) / 2, FONTDEF, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            StrMousePos temp = _getMousePos();
            switch (3*temp.y/SCREEN_H) {
            case 0:
                flag = EKnightMenu;
                break;
            case 1:
                break;
            case 2:
                break;
            }
        }
    }
    void _drawKnightMenu() {
        Rectangle temp;
        static int info[] = { size, col, row };
        temp.width = 103;
        temp.height = 100;
        for (int j = 0; j < 3; j++) {
            temp.y = 150 + 200 * j;
            for (int i = 0; i < 8; i++) {
                temp.x = 200 + 100 * i;
                DrawRectangleLinesEx(temp, 6, WHITE);
                DrawText(TextFormat("%d", i + 1), temp.x + 51 - MeasureText(TextFormat("%d", i + 1), FONTDEF)/2, temp.y + 50 - FONTDEF/2, FONTDEF, WHITE);
            }
            temp.x = 200 + 100 * (info[j] - 1);
            DrawRectangleLinesEx(temp, 6, GREEN);
        }
        DrawText("Size of the chessboard", (SCREEN_W - MeasureText("Size of the chessboard", FONTDEF)) / 2, 100 - FONTDEF / 2, FONTDEF, WHITE);
        DrawText("Number of the first column", (SCREEN_W - MeasureText("Number of the first column", FONTDEF)) / 2, 300 - FONTDEF / 2, FONTDEF, WHITE);
        DrawText("Number of the first row", (SCREEN_W - MeasureText("Number of the first row", FONTDEF)) / 2, 500 - FONTDEF / 2, FONTDEF, WHITE);       
        DrawRectangleLinesEx(temp, 6, GREEN);
        DrawRectangleLinesEx(temp, 6, GREEN);
        temp.width = 300;
        temp.x = 450;
        temp.y = 750;
        if (info[0] < info[1] || info[0] < info[2]) {
            DrawRectangleLinesEx(temp, 6, RED);
        }
        else {
            DrawRectangleLinesEx(temp, 6, WHITE);
        }
        DrawText("Generate", (SCREEN_W - MeasureText("Generate", FONTDEF)) / 2, 744 + FONTDEF / 2, FONTDEF, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            StrMousePos temp = _getMousePos();
            if (temp.y >= 156 && temp.y <= 656) {
                info[(temp.y - 156) / 200] = (temp.x - 106) / 100;
            }
            else if (temp.y >= 750 && temp.y <= 850 && temp.x >= 450 && temp.x <= 750 && info[0] >= info[1] && info[0] >= info[2]) {
                size = info[0];
                col = info[1];
                row = info[2];
                flag = EKnightAnswer;
            }
        }
    }
    void _generateKnight() {

    }
    void _drawKnightAnswer() {
        Rectangle temp;
        int x = 280, y = 50, side = 80;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if ((j + i) % 2) {
                    DrawRectangle(x + 80 * j, y + 80 * i, side, side, WHITE);
                }
                else {
                    DrawRectangle(x + 80 * j, y + 80 * i, side, side, BLUE);
                }
            }
        }
        temp.y = 750;
        temp.height = 100;
        temp.x = 50;
        temp.width = 500;
        DrawRectangleLinesEx(temp, 6, WHITE);
        DrawText("Generate next", temp.x + temp.width / 2 - MeasureText("Generate next", FONTDEF) / 2, temp.y - 6 + FONTDEF / 2, FONTDEF, WHITE);
        temp.x = 750;
        temp.width = 300;
        DrawRectangleLinesEx(temp, 6, WHITE);
        DrawText("Menu", temp.x + temp.width/2 - MeasureText("Menu", FONTDEF)/2, temp.y - 6 + FONTDEF / 2, FONTDEF, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            StrMousePos temp = _getMousePos();
            if (temp.y >= 744 && temp.y <= 856) {
                if (temp.x >= 44 && temp.x <= 556) {
                    
                }
                else if (temp.x >= 744 && temp.x <= 1056) {
                    flag = EMainMenu;
                }
            }
        }
    }
};

int main(void)
{
    InitWindow(1200, 900, "Chess problems");
    SetTargetFPS(30);
    MenuLogic menu;
    while (!WindowShouldClose())
    {
        menu._drawChoice();
    }
    CloseWindow();
    return 0;
}
