#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;

#define MAX_HEALTH_POINTS 100; 

typedef struct Player {
    float x;
    float y;
    float width; 
    float Health;
}Player;

typedef struct Enemy {
    float x;
    float y;
    float EnemyHealth;
}Enemy;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 580;

    static Player player;

    player.width = 20;
    player.x = -100;
    player.y = 320;

    //int MaxCircleEnemyHP = 100;
    //int CircleEnemyHP = 100;
    //int MaxCircleHP = 100;
    //int CircleHP = 100;

    //string inputString;

    InitWindow(screenWidth, screenHeight, "CodeCutters");

    Font font = LoadFont("resources/TiltWarp-Regular-VariableFont_XROT,YROT.ttf");

    Image image = LoadImage("resources/background.png");
    Texture2D texture = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    Texture2D character = LoadTexture("resources/character1.png");

    SetTargetFPS(60);     // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyDown(KEY_RIGHT)) player.x += 3;
        if (IsKeyDown(KEY_LEFT)) player.x -= 3;


        if (player.x <= -115)
            player.x = -115;
        if (player.x >= 715)
            player.x = 715;

        /*collision = CheckCollisionCircles(Circle, 20, CircleEnemy, 20);*/

        // Draw
        BeginDrawing();

        DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);
        DrawTexture(character, player.x, player.y, WHITE);

        //if (collision == true) {
        //    HasHit = true;
        //}
        //if (HasHit) {
        //    player.x = 520;

        //    DrawRectangle(Circle.x - 30, Circle.y - 44, 70, 20, GRAY);
        //    DrawRectangle(Circle.x - 30, Circle.y - 44, (70 * CircleHP) / MaxCircleHP, 20, GREEN);
        //    DrawTextEx(font, to_string(CircleHP).c_str(), Vector2{ Circle.x - 10, Circle.y - 44 }, 20, 0, BLACK);

        //    DrawRectangle(CircleEnemy.x - 30, CircleEnemy.y - 44, 70, 20, GRAY);
        //    DrawRectangle(CircleEnemy.x - 30, CircleEnemy.y - 44, (70 * CircleEnemyHP) / MaxCircleEnemyHP, 20, GREEN);
        //    DrawTextEx(font, to_string(CircleEnemyHP).c_str(), Vector2{ CircleEnemy.x - 10, CircleEnemy.y - 44 }, 20, 0, BLACK);

        //    DrawText(inputString.c_str(), 50, 50, 20, BLACK);

        //}

        //else if (!collision) {
            
        //}


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