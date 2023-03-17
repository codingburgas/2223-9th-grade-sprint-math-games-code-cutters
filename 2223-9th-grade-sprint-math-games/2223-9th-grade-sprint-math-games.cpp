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

void randomise(int number1, int number2) {
    number1 = GetRandomValue(1, 15);
    number2 = GetRandomValue(1, 15);
}

static int MAX_HEALTH_POINTS = 100;

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

    int number_1 = GetRandomValue(1, 15);
    int number_2 = GetRandomValue(1, 15);

    string question = "What's " + to_string(number_1) + " << " + to_string(number_2) + "?";
    string buttonPress = "Press K to type. To submit press ENTER";
    string answer;

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
            DrawRectangle(player.x + 115, player.y + 30, (70 * player.Health) / MAX_HEALTH_POINTS, 20, GREEN);
            DrawTextEx(font, to_string(player.Health).c_str(), Vector2{ player.x + 135, player.y + 30 }, 20, 0, BLACK);

            DrawRectangle(enemy.x + 360, enemy.y + 100, 70, 20, GRAY);
            DrawRectangle(enemy.x + 315, enemy.y + 100, (130 * enemy.EnemyHealth) / MAX_HEALTH_POINTS, 22, GREEN);
            DrawTextEx(font, to_string(enemy.EnemyHealth).c_str(), Vector2{ enemy.x + 362, enemy.y + 98 }, 25, 0, BLACK);

            DrawTextEx(font, question.c_str(), Vector2{ 100, 190 }, 38, 1, WHITE);
            DrawTextEx(font, buttonPress.c_str(), Vector2{ 70, 150 }, 35, 1, WHITE);
            DrawTextEx(font, answer.c_str(), Vector2{ 120, 210 }, 40, 1, WHITE);

            if (IsKeyPressed('K')) {
                cin >> answer;
            }
        }

        else if (!collision) {
            if (IsKeyDown('D')) player.x += 3.0f;
            if (IsKeyDown('A')) player.x -= 3.0f;
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