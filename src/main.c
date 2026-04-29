#include <stdio.h>

#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;
const int edge = 25;

void drawBall(int x , int y , Color colouring) {
    DrawCircle(x, y, 25, colouring);
}

void manual() {
    DrawText("Press Arrow-Keys to move Ball" , 200 , 0 , 25 ,GRAY);
    DrawText("Botond Payerhofer" , 600 , 420 , 20 ,LIGHTGRAY);
}

int main(void)
{
    const int speed = 5;


    InitWindow(screenWidth, screenHeight, "Raylib Ball Game");
    SetTargetFPS(60);

    int x = screenWidth /2;
    int y = screenHeight /2;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(10, 10);
        manual();
        drawBall(x , y , BLUE);

        if (IsKeyDown(KEY_RIGHT) && screenWidth - edge > x) {
            x = x + speed;
        }
        else if (IsKeyDown(KEY_LEFT) && edge < x){
            x = x - speed;
        }
        else if (IsKeyDown(KEY_UP) && edge < y){
            y = y - speed;
        }
        else if (IsKeyDown(KEY_DOWN) && screenHeight - edge > y){
            y = y + speed;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
