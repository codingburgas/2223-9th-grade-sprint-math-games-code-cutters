#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;

void ChooseRectangle(bool& flag, Rectangle rectangle) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), rectangle)) {
            flag = true;
        }
    }
}

int main(void)
{
    // Initialization
    const int screenWidth = 899;
    const int screenHeight = 580;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Font font = LoadFont("resources/TiltWarp-Regular-VariableFont_XROT,YROT.ttf");

    Texture2D background = LoadTexture("resources/background2.png");
    Texture2D button1 = LoadTexture("resources/Playbutton.png");
    Texture2D button2 = LoadTexture("resources/Quitbutton.png");

    Rectangle PlayButton = { screenWidth / 2 , screenHeight / 2 , 30, 10 };

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        ClearBackground(RAYWHITE);
        BeginDrawing();


        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, WHITE);
        DrawTextEx(font, "Game Name", { screenWidth / 2 - 180 , 70 }, 90, 1, WHITE);
        DrawTexture(button1, screenWidth / 2 - 120 , screenHeight / 2 - 90, WHITE);
        DrawTexture(button2, screenWidth / 2 - 125, screenHeight / 2 + 40, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}