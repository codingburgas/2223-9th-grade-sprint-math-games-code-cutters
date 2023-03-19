#include "raylib.h" //raylib setup
#include <iostream>
#include <string>
#include <stdlib.h> //s.rand rand
#include <time.h> // time

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
    bool isAlive;
}Enemy;

int IntegerCheck(int num2) {
    int num1 = GetRandomValue(1, 5) * pow(2, num2);
    return num1;
}



int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 580;

    static Player player;
    static Enemy enemy;

    player.Health = 100;
    enemy.EnemyHealth = 100;
    bool flag = false;
    enemy.isAlive = true;

    player.x = -100;
    player.y = 340;
    enemy.x = 310;
    enemy.y = 155;

    bool collision = false;
    bool HasHit = false;


    int input_number = 564386;
    string Answer = "Your answer: " + to_string(input_number);

    InitWindow(screenWidth, screenHeight, "CodeCutters");

    Font font = LoadFont("resources/TiltWarp-Regular-VariableFont_XROT,YROT.ttf");

    static Image image = LoadImage("resources/background.png");
    static Texture2D texture = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    static Texture2D player1 = LoadTexture("resources/character1.png");
    static Texture2D enemy1 = LoadTexture("resources/enemy.png");

    int value_2 = GetRandomValue(1, 5);
    int value_1 = IntegerCheck(value_2);


    SetTargetFPS(60);     // Set our game to run at 60 frames-per-second


    Rectangle playerRec = { player.x, player.y, float(player1.width), float(player1.height) };
    Rectangle enemyRec = { 750, 400, float(enemy1.width), float(enemy1.height) };
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        playerRec = { player.x, player.y, float(player1.width), float(player1.height) };

        if (player.x <= -115.0f)
            player.x = -115.0f;
        if (player.x >= 715.0f)
            player.x = 715.0f;

        collision = CheckCollisionRecs(playerRec, enemyRec);



        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);

        if (enemy.isAlive) {
            DrawTexture(player1, player.x, player.y, WHITE);
            DrawTexture(enemy1, enemy.x, enemy.y, WHITE);
        }



        if (collision) {
            HasHit = true;
        }
        if (HasHit) {

            player.x = 400;

            DrawRectangle(player.x + 115, player.y + 30, 70, 20, GRAY);
            DrawRectangle(player.x + 115, player.y + 30, (70 * player.Health) / 100, 20, GREEN);
            DrawTextEx(font, to_string(player.Health).c_str(), Vector2{ player.x + 135, player.y + 30 }, 20, 0, BLACK);

            DrawRectangle(enemy.x + 315, enemy.y + 100, 130, 20, GRAY);
            DrawRectangle(enemy.x + 315, enemy.y + 100, (130 * enemy.EnemyHealth) / 100, 20, GREEN);
            DrawTextEx(font, to_string(enemy.EnemyHealth).c_str(), Vector2{ enemy.x + 365, enemy.y + 98 }, 25, 0, BLACK);

            string text = "What is " + to_string(value_1) + " >> " + to_string(value_2) + "?";

            DrawText(text.c_str(), 220, 220, 38, WHITE);


            if (IsKeyPressed('R')) {
                cin >> input_number;
                flag = false;
            }
            if (input_number != 564386) {
                Answer = "Your answer: " + to_string(input_number);
                DrawText(Answer.c_str(), 220, 250, 38, WHITE);
            }
            if (input_number == (value_1 >> value_2) && flag == false) {
                enemy.EnemyHealth -= 20;
                flag = true;

                value_2 = GetRandomValue(1, 5);
                value_1 = IntegerCheck(value_2);
            }
            else if (flag == false && input_number != 564386) {
                player.Health -= 20;
                flag = true;

                value_2 = GetRandomValue(1, 5);
                value_1 = IntegerCheck(value_2);
            }

            if (enemy.EnemyHealth == 0) {
                UnloadTexture(enemy1);
                if (player.Health != 100) {
                    player.Health += 20; //Heals after a level
                }
                HasHit = false;
            }
            if (player.Health == 0) {
                UnloadTexture(player1);
                HasHit = false;
                CloseWindow();
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