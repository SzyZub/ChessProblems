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
    EQueenMenu,
    EKnightAnswer,
    EQueenAnswer,
    EExit
} EnMenuFlags;

class GeneratorK {
public:
    int size, reCalc, gened;
    int answer[8][8];
    int moves[63];
    GeneratorK() {}
    GeneratorK(int s) : size(s) { 
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
        for (int i = 0; i < 63; i++) 
            moves[i] = -2;
        for (int i = 0; i < size * size - 1; i++)
            moves[i] = -1;
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
    void _generate(int startX, int startY) {
        int count = 1;
        answer[startX][startY] = count;
        int nx, ny, i = 0, j = 0;
        if (size == 1) {
            gened = 1;
            return;
        }
        if (reCalc == 1) {
            i = size * size - 2;
            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    if (answer[x][y] == size*size) {
                        answer[x][y] = -1;
                        startX = x;
                        startY = y;
                        _calcPrev(startX, startY, i);
                        nx = startX;
                        ny = startY;
                    }
                }
            }
            j = moves[size * size - 2] + 1;
            moves[size * size - 2] = -1;
            count = size * size - 1;
            reCalc = 0;
        }
        while (i < size * size - 1) {
            if (j >= 8) {
                answer[startX][startY] = -1;
                count--;
                i--;
                if (i == -1) {
                    gened = 0;
                    return;
                }
                _calcPrev(startX, startY, i);
                nx = startX;
                ny = startY;
                j = moves[i] + 1;
                moves[i] = -1;
            }
            while (j < 8) {
                if (_check(j, nx, ny, startX, startY)) {
                    count++;
                    answer[nx][ny] = count;
                    moves[i] = j;
                    if (count == size * size) {
                        gened = 1;
                        return;
                    }
                    break;
                }
                j++;
            }
            if (j != 8){
                startX = nx;
                startY = ny;
                i++;
                j = 0;
            }           
        }
        gened = 0;
        return;
    }
    void _calcPrev(int& startX, int& startY, int count) {
        switch (moves[count]) {
        case 0:
            startX = startX - 2;
            startY = startY - 1;
            break;
        case 1:
            startX = startX - 1;
            startY = startY - 2;
            break;
        case 2:
            startX = startX + 1;
            startY = startY - 2;
            break;
        case 3:
            startX = startX + 2;
            startY = startY - 1;
            break;
        case 4:
            startX = startX + 2;
            startY = startY + 1;
            break;
        case 5:
            startX = startX + 1;
            startY = startY + 2;
            break;
        case 6:
            startX = startX - 1;
            startY = startY + 2;
            break;
        case 7:
            startX = startX - 2;
            startY = startY + 1;
            break;
        }
    }
};

class GeneratorQ {
public:
    int size, reCalc, gened;
    int answer[8][8];
    GeneratorQ() {}
    GeneratorQ(int s) : size(s) {
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
    void _generate(int startX, int startY) {
        int count, i, j, broken = 0;
        if (size == 1) {
            gened = 1;
            return;
        }
        if (reCalc == 1) {
            count = size + 1;
            int temp = (startY - 1) % size;
            if (temp == -1) {
                temp = size - 1;
            }
            for (int x = 0; x < size; x++) {
                if (answer[temp][x] >= size) {
                    _remove(x, temp, count);
                    j = x + 1;
                    i = temp;
                    }
            }
            reCalc = 0;
        }
        else {
            count = 1;
            _fill(startX, startY, count);
            i = (startY + 1) % size;
            j = 0;
        }
        while(1) {
            while(1) {
                std::cout << i << " " << j << std::endl;
                _printSol();
                if (answer[i][j] == -1) {
                    _fill(j, i, count);
                    if (count == size + 1) {
                        gened = 1;
                        return;
                    }
                    j = 0;
                    i = (i + 1) % size;
                    break;
                }
                else if (j >= size - 1) {
                    for (int b = 0; b < size; b++) {
                        if (answer[i - 1 >= 0 ? i - 1 : size - 1][b] >= size) {
                            _remove(b, i - 1, count);                         
                            if (count == 1) {
                                gened = 0;
                                return;
                            }
                            j = b + 1;
                            i = (i - 1) % size;
                            if (i == -1) {
                                i = size - 1;
                            }
                            broken = 1;
                            break;
                        }
                    }
                }
                if (!broken) {
                    j++;
                }
                else {
                    broken = 0;
                }
            }
        }
    }
    void _fill(int nx, int ny, int &count) {
        answer[ny][nx] = answer[ny][nx] + size + count;
        for (int i = 0; i < size; i++) {
            answer[ny][i]++;
            answer[i][nx]++;
        }
        for (int i = 0; ny + i != size && nx + i != size; i++) {
            answer[ny + i][nx + i]++;
        }
        for (int i = 0; ny + i != size && nx - i != -1; i++) {
            answer[ny + i][nx - i]++;
        }
        for (int i = 0; ny - i != -1 && nx + i != size; i++) {
            answer[ny - i][nx + i]++;
        }
        for (int i = 0; ny - i != -1 && nx - i != -1; i++) {
            answer[ny - i][nx - i]++;
        }
        count++;
    }
    void _remove(int nx, int ny, int& count) {
        answer[ny][nx] = answer[ny][nx] - size - count + 1;
        for (int i = 0; i < size; i++) {
            answer[ny][i]--;
            answer[i][nx]--;
        }
        for (int i = 0; ny + i != size && nx + i != size; i++) {
            answer[ny + i][nx + i]--;
        }
        for (int i = 0; ny + i != size && nx - i != -1; i++) {
            answer[ny + i][nx - i]--;
        }
        for (int i = 0; ny - i != -1 && nx + i != size; i++) {
            answer[ny - i][nx + i]--;
        }
        for (int i = 0; ny - i != -1 && nx - i != -1; i++) {
            answer[ny - i][nx - i]--;
        }
        count--;
    }
    void _printSol() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << answer[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};

class MenuLogic {
private:
    int size, col, row;
    GeneratorK genK;
    GeneratorQ genQ;
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
            _drawMenu(0);
            break;
        case EQueenMenu:
            _drawMenu(1);
            break;
        case EKnightAnswer:
            _drawKnightAnswer();
            break;
        case EQueenAnswer:
            _drawQueenAnswer();
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
                flag = EQueenMenu;
                break;
            case 2:
                flag = EExit;
                break;
            }
        }
    }
    void _drawMenu(int choice) {
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
                if (choice == 0) {
                    _drawMenuK();
                }
                else {
                    _drawMenuQ();
                }
            }
        }
    }
    void _drawMenuK() {
        genK = GeneratorK(size);
        int x = row - 1, y = col - 1;
        genK._generate(x, y);
        flag = EKnightAnswer;
    }
    void _drawMenuQ() {
        genQ = GeneratorQ(size);
        int x = row - 1, y = col - 1;
        genQ._generate(x, y);
        genQ._printSol();
        flag = EQueenAnswer;
    }
    void _drawKnightAnswer() {
        Rectangle temp;
        int x = 600 - 40 * size, y = 50, side = 80;
        if (genK.gened == 1) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if ((j + i) % 2) {
                        DrawRectangle(x + 80 * j, y + 80 * i, side, side, WHITE);
                    }
                    else {
                        DrawRectangle(x + 80 * j, y + 80 * i, side, side, BLUE);
                    }
                    DrawText(TextFormat("%d", genK.answer[j][i]),  x + 80 * j + (80 - MeasureText(TextFormat("%d", genK.answer[j][i]), FONTDEF)) / 2,    y + 80 * i + (80 - FONTDEF) / 2, FONTDEF, BLACK);
                }
            }
        }
        else {
            DrawText("Answer doesn't exist", (SCREEN_W - MeasureText("Answer doesn't exist", FONTDEF)) / 2, SCREEN_H / 2 - FONTDEF, FONTDEF, WHITE);
        }
        temp.y = 750;
        temp.height = 100;
        temp.x = 50;
        temp.width = 500;
        DrawRectangleLinesEx(temp, 6, genK.gened ? WHITE : RED);
        DrawText("Generate next", temp.x + temp.width / 2 - MeasureText("Generate next", FONTDEF) / 2, temp.y - 6 + FONTDEF / 2, FONTDEF, WHITE);
        temp.x = 750;
        temp.width = 300;
        DrawRectangleLinesEx(temp, 6, WHITE);
        DrawText("Menu", temp.x + temp.width/2 - MeasureText("Menu", FONTDEF)/2, temp.y - 6 + FONTDEF / 2, FONTDEF, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            StrMousePos temp = _getMousePos();
            if (temp.y >= 744 && temp.y <= 856) {
                if (temp.x >= 44 && temp.x <= 556 && genK.gened == 1) {
                    int x = row - 1, y = col - 1;
                    genK.reCalc = 1;
                    genK._generate(x, y);
                }
                else if (temp.x >= 744 && temp.x <= 1056) {
                    flag = EMainMenu;
                }
            }
        }
    }
    void _drawQueenAnswer() {
        Rectangle temp;
        int x = 600 - 40 * size, y = 50, side = 80;
        if (genQ.gened == 1) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if ((j + i) % 2) {
                        DrawRectangle(x + 80 * j, y + 80 * i, side, side, WHITE);
                    }
                    else {
                        DrawRectangle(x + 80 * j, y + 80 * i, side, side, BLUE);
                    }
                    if (genQ.answer[j][i] < size) {
                        DrawText("Q", x + 80 * j + (80 - MeasureText("Q", FONTDEF)) / 2, y + 80 * i + (80 - FONTDEF) / 2, FONTDEF, BLACK);
                    }     
                }
            }
        }
        else {
            DrawText("Answer doesn't exist", (SCREEN_W - MeasureText("Answer doesn't exist", FONTDEF)) / 2, SCREEN_H / 2 - FONTDEF, FONTDEF, WHITE);
        }
        temp.y = 750;
        temp.height = 100;
        temp.x = 50;
        temp.width = 500;
        DrawRectangleLinesEx(temp, 6, genQ.gened ? WHITE : RED);
        DrawText("Generate next", temp.x + temp.width / 2 - MeasureText("Generate next", FONTDEF) / 2, temp.y - 6 + FONTDEF / 2, FONTDEF, WHITE);
        temp.x = 750;
        temp.width = 300;
        DrawRectangleLinesEx(temp, 6, WHITE);
        DrawText("Menu", temp.x + temp.width / 2 - MeasureText("Menu", FONTDEF) / 2, temp.y - 6 + FONTDEF / 2, FONTDEF, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            StrMousePos temp = _getMousePos();
            if (temp.y >= 744 && temp.y <= 856) {
                if (temp.x >= 44 && temp.x <= 556 && genQ.gened == 1) {
                    int x = row - 1, y = col - 1;
                    genQ.reCalc = 1;
                    genQ._generate(x, y);
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
