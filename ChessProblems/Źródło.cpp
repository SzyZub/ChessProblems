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
    EKnightAnswer,
    EExit
} EnMenuFlags;

class Generator {
    int size, reCalc;
    int answer[8][8];
public:
    Generator(){}
    Generator(int s) : size(s) { 
        reCalc = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                answer[i][j] = -2;
            }
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                answer[i][j] = -1;
            }
        }
    }
    bool _check(int option, int &nx, int &ny, int startX, int startY) {
        switch (option) {
        case 0:
            nx = startX + 2;
            ny = startY + 1;
            break;
        case 1:
            nx = startX + 1;
            ny = startY + 2;
            break;
        case 2:
            nx = startX - 1;
            ny = startY + 2;
            break;
        case 3:
            nx = startX - 2;
            ny = startY + 1;
            break;
        case 4:
            nx = startX - 2;
            ny = startY - 1;
            break;
        case 5:
            nx = startX - 1;
            ny = startY - 2;
            break;
        case 6:
            nx = startX + 1;
            ny = startY - 2;
            break;
        case 7:
            nx = startX + 2;
            ny = startY - 1;
            break;
        }
        if (ny < size && ny >= 0 && nx < size && nx >= 0 && answer[nx][ny] == -1) {
            return true;
        }
        return false;
    }
    bool _generate(int count, int startX, int startY) {
        answer[startX][startY] = count;
        int nx, ny;
        if (count == size * size) {
            return true;
        }
        else {
            for (int i = 0; i < 8; i++) {
                if (_check(i, nx, ny, startX, startY) == true) {
                    if (_generate(count + 1, nx, ny) == true) {
                        if (reCalc == 1) {
                            reCalc = 0;
                        }
                        else {
                            return true;
                        }
                    }
                }
            }
            answer[startX][startY] = -1;
        }
        return false;
    }
    void _printSolution()
    {
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++)
                std::cout << answer[x][y] << '\t';
            std::cout << std::endl;
        }
    }
};

class MenuLogic {
private:
    int size, col, row;
    Generator gen;
public:
    EnMenuFlags flag;
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
                flag = EExit;
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
        temp.width = 900;
        temp.x = 150;
        temp.y = 750;
        DrawRectangleLinesEx(temp, 6, (info[0] < info[1] || info[0] < info[2]) ? RED : WHITE);
        DrawText("Proceed to generation menu", (SCREEN_W - MeasureText("Proceed to generation menu", FONTDEF)) / 2, 744 + FONTDEF / 2, FONTDEF, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            StrMousePos temp = _getMousePos();
            if (((temp.y >= 150 && temp.y <= 250) || (temp.y >= 350 && temp.y <= 450) || (temp.y >= 550 && temp.y <= 650)) && temp.x >= 200 && temp.x <= 1000) {
                info[(temp.y - 150) / 200] = (temp.x - 100) / 100;
            }
            else if (temp.y >= 750 && temp.y <= 850 && temp.x >= 450 && temp.x <= 750 && info[0] >= info[1] && info[0] >= info[2]) {
                size = info[0];
                col = info[1];
                row = info[2];
                gen = Generator(size);
                int x = row - 1, y = col - 1;
                gen._generate(1, x, y);
                gen._printSolution();
                flag = EKnightAnswer;
            }
        }
    }
    void _drawKnightAnswer() {
        Rectangle temp;
        int x = 600 - 40 * size, y = 50, side = 80;
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
                    int x = row - 1, y = col - 1;
                    gen._generate(1, x, y);
                    gen._printSolution();
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
        if (menu.flag == EExit) {
            return 0;
        }
    }
    CloseWindow();
    return 0;
}
