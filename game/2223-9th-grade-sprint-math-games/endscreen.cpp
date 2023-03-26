#include "raylib.h"
#include <iostream>
#include <string>


using namespace std;


int main()
{
    // Initialization
    const int screenWidth = 899;
    const int screenHeight = 580;

    InitWindow(screenWidth, screenHeight, "Binary Battle");
    InitAudioDevice();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Font font = LoadFont("resources/TiltWarp-Regular-VariableFont_XROT,YROT.ttf");

    Texture2D background = LoadTexture("resources/background2.png");
    Texture2D GameName = LoadTexture("resources/GameName.png");
    Texture2D Quit = LoadTexture("resources/Quitbutton.png");
    Texture2D YouWinButton = LoadTexture("resources/YouWin.png");
    Texture2D YouLoseButton = LoadTexture("resources/YouLose.png");

    bool played = false;

    bool YouWin = false;
    bool YouLose = true;

    Sound music = LoadSound("resources/music.mp3");

    Rectangle QuitButton = { screenWidth / 2 - 125, screenHeight / 2 + 120, 250, 100 };
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        BeginDrawing();
        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, RAYWHITE);
        if (YouWin) {
            DrawTexture(YouWinButton, -90, 10, RAYWHITE);
        }
        else if (YouLose) {
            DrawTexture(YouLoseButton, -90, 10, RAYWHITE);
        }
        
        DrawTexture(Quit, screenWidth / 2 - 125, screenHeight / 2 + 40, RAYWHITE);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    CloseAudioDevice();
    //--------------------------------------------------------------------------------------

    return 0;
}