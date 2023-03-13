#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;

typedef struct Player {
    float x;
    float y;
    int Health;
}Player;

typedef struct Enemy {
    float x;
    float y;
    int EnemyHealth;
}Enemy;


int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 580;

    static Player player;
    static Enemy enemy;

    player.x = -100;
    player.y = 340;
    enemy.x = 310;
    enemy.y = 155;

    bool collision = false;
    bool HasHit = false;


    InitWindow(screenWidth, screenHeight, "CodeCutters");

    Font font = LoadFont("resources/TiltWarp-Regular-VariableFont_XROT,YROT.ttf");

    static Image image = LoadImage("resources/background.png");
    static Texture2D texture = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    static Texture2D player1 = LoadTexture("resources/character1.png");
    static Texture2D enemy1 = LoadTexture("resources/enemy.png");

    
    

    SetTargetFPS(60);     // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Rectangle playerRec = { player.x, player.y, float(player1.width), float(player1.height) };
        Rectangle enemyRec = { 750, 400, float(enemy1.width), float(enemy1.height) };

        if (player.x <= -115)
            player.x = -115;
        if (player.x >= 715)
            player.x = 715;

        collision = CheckCollisionRecs(playerRec, enemyRec);

        // Draw
        BeginDrawing();

        DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);
        DrawTexture(player1, player.x, player.y, WHITE);
        DrawTexture(enemy1, enemy.x, enemy.y, WHITE);
        

        if (collision) {
            HasHit = true;
        }
        if (HasHit) {
            player.x = 400;
            player.Health = 100;
            enemy.EnemyHealth = 100;

            DrawRectangle(player.x + 115, player.y + 30, 70, 20, GRAY);
            DrawRectangle(player.x + 115, player.y + 30, (70 * player.Health) / 100, 20, GREEN);
            DrawTextEx(font, to_string(player.Health).c_str(), Vector2{ player.x + 135, player.y + 30 }, 20, 0, BLACK);

            DrawRectangle(enemy.x + 360, enemy.y + 100, 70, 20, GRAY);
            DrawRectangle(enemy.x + 315, enemy.y + 100, (130 * enemy.EnemyHealth) / 100, 22, GREEN);
            DrawTextEx(font, to_string(enemy.EnemyHealth).c_str(), Vector2{ enemy.x + 362, enemy.y + 98 }, 25, 0, BLACK);
        }

        else if (!collision) {
            if (IsKeyDown('D')) player.x += 25;
            if (IsKeyDown('A')) player.x -= 3;
        }


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);       // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}