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

void AnimateLeft(float& timer, int& frame, int maxFrames, float frameWidth, Texture2D Run, float& x1, float& y1) {
    timer += GetFrameTime();
    if (timer >= 0.2f) {
        timer = 0.0f;
        frame += 1;
    }

    frame = frame % maxFrames;
    DrawTextureRec(Run, Rectangle{ (frameWidth * frame), 0, frameWidth, (float)Run.width }, Vector2{ x1, y1 }, RAYWHITE);
}

typedef struct Player {
    float x;
    float y;
}Player;


int baba(void)
{
    // Initialization
    const int screenWidth = 890;
    const int screenHeight = 580;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    static Player player;

    Texture2D Run = LoadTexture("resources/runA.png");
    Texture2D Run2 = LoadTexture("resources/runB.png");
    float frameWidth = (float)(Run.width / 8);
    float timer = 0.0f;
    int frame = 0;
    int maxFrames = (int)(Run.width / (int)frameWidth);

    player.x = 100;
    player.y = 0;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        ClearBackground(RAYWHITE);
        BeginDrawing();
        if (IsKeyDown('D')) {
            player.x += 3.0f;
            AnimateLeft(timer, frame, maxFrames, frameWidth, Run, player.x, player.y);
        }
        else if (IsKeyDown('A')) {
            player.x -= 3.0f;
            AnimateLeft(timer, frame, maxFrames, frameWidth, Run, player.x, player.y);
        }
        else{
            DrawTextureRec(Run, Rectangle{ (frameWidth * frame), 0, frameWidth, (float)Run.width }, Vector2{ player.x, player.y }, RAYWHITE);
        }

        //}

        cout << frame << endl;


        


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}