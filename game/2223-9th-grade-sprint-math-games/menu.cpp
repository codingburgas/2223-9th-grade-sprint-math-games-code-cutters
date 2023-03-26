#include "raylib.h"
#include "menu.h"


using namespace std;

//Checks whether a button is clicked
bool ChooseRectangle(Rectangle rectangle) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), rectangle)) {
            return true;
        }
    }
}

int main()
{
    // Initialization
    const int screenWidth = 899;
    const int screenHeight = 580;

    InitWindow(screenWidth, screenHeight, "Binary Battle");
    InitAudioDevice();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Font font = LoadFont("resources/TiltWarp-Regular-VariableFont_XROT,YROT.ttf");

    Texture2D testenemy = LoadTexture("resources/enemy2.png");
    Texture2D background = LoadTexture("resources/background2.png");
    Texture2D GameName = LoadTexture("resources/GameName.png");
    Texture2D button1 = LoadTexture("resources/Playbutton.png");
    Texture2D button2 = LoadTexture("resources/Quitbutton.png");
    Texture2D portal = LoadTexture("resources/protal.png");

    bool played = true;

    Sound music = LoadSound("resources/music.mp3");

    Rectangle PlayButton = { screenWidth / 2 - 120, screenHeight / 2 - 10, 250, 100 };
    Rectangle QuitButton = { screenWidth / 2 - 125, screenHeight / 2 + 120, 250, 100 };
    PlaySound(music);
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        BeginDrawing();
        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, WHITE);
        DrawTexture(GameName, -80, -80, WHITE);
        DrawTexture(button1, screenWidth / 2 - 120, screenHeight / 2 - 10, WHITE);
        DrawTexture(button2, screenWidth / 2 - 125, screenHeight / 2 + 120, WHITE);
        
        if (IsKeyPressed(KEY_SPACE) == true && played == false) {
            PlaySound(music);
            played = true;
        }
        else if (IsKeyPressed(KEY_SPACE) == true && played == true){
            StopSound(music);
            played = false;
        }

        if (ChooseRectangle(PlayButton)) {
            CloseAudioDevice();
            game();
        }

        if (ChooseRectangle(QuitButton)) {
            EndDrawing();
            CloseWindow();
            CloseAudioDevice();
            return 0;
        }
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