#include "raylib.h"
#include "endscreen.h"


using namespace std;

//after the game has come to an end, this screen shows up
void endscreen(bool YouWin, bool YouLose)
{
    // Initialization
    const int screenWidth = 899;
    const int screenHeight = 580;

    InitAudioDevice();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Font font = LoadFont("resources/TiltWarp-Regular-VariableFont_XROT,YROT.ttf");

    Texture2D background = LoadTexture("resources/background2.png");
    Texture2D GameName = LoadTexture("resources/GameName.png");
    Texture2D Quit = LoadTexture("resources/Quitbutton.png");
    Texture2D YouWinButton = LoadTexture("resources/YouWin.png");
    Texture2D YouLoseButton = LoadTexture("resources/YouLose.png");

    Sound music = LoadSound("resources/music.mp3");
    bool played = true;

    Rectangle QuitButton = { screenWidth / 2 - 125, screenHeight / 2 + 40, 250, 100 };
    PlaySound(music);
    // Main game loop
    while (true)  
    {

        if (IsKeyPressed(KEY_SPACE) == true && played == false) {
            PlaySound(music);
            played = true;
        }
        else if (IsKeyPressed(KEY_SPACE) == true && played == true) {
            StopSound(music);
            played = false;
        }
        if (WindowShouldClose()) {
            EndDrawing();
            return;
        }
        BeginDrawing();
        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, RAYWHITE);
        if (YouWin) {
            DrawTexture(YouWinButton, -90, 10, RAYWHITE);
        }
        else if (YouLose) {
            DrawTexture(YouLoseButton, -90, 10, RAYWHITE);
        }

        DrawTexture(Quit, screenWidth / 2 - 125, screenHeight / 2 + 40, RAYWHITE);

        //
        if (ChooseRectangle(QuitButton)) {
            EndDrawing();
            CloseWindow();
            CloseAudioDevice();
            return;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();
    //--------------------------------------------------------------------------------------

}