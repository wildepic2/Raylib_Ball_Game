#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

//Function Prototypes
void manual();
void ball2(int *x , int *y , int *xMultiplier , int *yMultiplier);
void playerInput(int *x , int *y);
int collision(int x , int y , int x2 , int y2);

//Constantes for Game
const int screenWidth = 800;
const int screenHeight = 450;
const int edge = 25;
const int speedBall = 5;
const int speedBall2 = 5;
const int allStateColor = 6;

//Variables for Game
int stateColor = 0;
bool isCollision = false;

int main(void)
{
    //Inits the window
    InitWindow(screenWidth, screenHeight, "Raylib Ball Game");
    //Sets the fps
    SetTargetFPS(60);

    //Inits the two balls at the start
    int x = screenWidth /2;
    int y = screenHeight /2;
    int x2 = screenWidth /2 + 50;
    int y2 = screenHeight /2 + 50;

    //Inits the var that it can move in every direction
    int xMultiplier = speedBall2;
    int yMultiplier = speedBall2;

    //Main game loop open until you dont close window
    while (!WindowShouldClose()) {
        //Inits the drawing system
        BeginDrawing();

        //Sets an white Background
        ClearBackground(RAYWHITE);

        //Draws the current fps
        DrawFPS(10, 10);

        //Draws the help how do you move the player
        manual();

        //Draws the ball1
        DrawCircle(x , y , 25 ,BLUE);

        //Calls the function for ball2
        ball2(&x2 , &y2 , &xMultiplier , &yMultiplier);

        //Player input Handling
        playerInput(&x , &y);

        //Switches State color if collision ends
        stateColor = collision(x , y , x2 , y2);

        //Stops the drawing and makes some things in background like waiting for frame to have solid fps
        EndDrawing();
    }

    //Fully Closes the window
    CloseWindow();
    return 0;
}

void manual() {
    DrawText("Press Arrow-Keys to move Ball" , 200 , 0 , 25 ,GRAY);
    DrawText("Botond Payerhofer" , 600 , 420 , 20 ,LIGHTGRAY);
}

void ball2(int *x , int *y , int *xMultiplier , int *yMultiplier) {
    //Switches the color of the ball2 based on the stateColor
    switch (stateColor) {
        case 0:
            DrawCircle(*x , *y , 25 ,MAGENTA);
            break;
        case 1:
            DrawCircle(*x , *y , 25 ,RED);
            break;
        case 2:
            DrawCircle(*x , *y , 25 ,GREEN);
            break;
        case 3:
            DrawCircle(*x , *y , 25 ,YELLOW);
            break;
        case 4:
            DrawCircle(*x , *y , 25 ,PURPLE);
            break;
        case 5:
            DrawCircle(*x , *y , 25 ,ORANGE);
            break;
        case 6:
            DrawCircle(*x , *y , 25 ,BROWN);
            break;
    }

    //Moves the ball2
    *x += *xMultiplier;
    *y += *yMultiplier;

    //Reverse direction ball2
    if (*x >= screenWidth - edge || *x <= edge ) {
        *xMultiplier *= -1;
    }
    else if (*y >= screenHeight - edge || *y <= edge ) {
        *yMultiplier *= -1;
    }
}
void playerInput(int *x , int *y) {
    //Player Input
    if (IsKeyDown(KEY_RIGHT) && screenWidth - edge > *x) {
        *x = *x + speedBall;
    }
    else if (IsKeyDown(KEY_LEFT) && edge < *x){
        *x = *x - speedBall;
    }
    else if (IsKeyDown(KEY_UP) && edge < *y){
        *y = *y - speedBall;
    }
    else if (IsKeyDown(KEY_DOWN) && screenHeight - edge > *y){
        *y = *y + speedBall;
    }
}

int collision(int x , int y , int x2 , int y2) {
    //Defines Vektor 2 of balls
    Vector2 circle1 = (Vector2){ x , y };
    Vector2 circle2 = (Vector2){ x2 , y2 };

    //Check for Collision
    if (CheckCollisionCircles(circle1, 25 , circle2 , 25)) {
        //Makes that so that the color changes per collision one time and the isCollision needs to reset
        //to allow next color change
        if (isCollision == false) {
            isCollision = true;
            stateColor++;
        }

        //If no more statecolors restart from beginning
        if (stateColor >= allStateColor) {
            stateColor = 0;
        }
    }
    else {
        //Resets the isCollision if no more collision
        isCollision = false;
    }
    return stateColor;
}