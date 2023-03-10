#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;

void QuestionsandAnswers(string str) {
    if (IsKeyPressed(KEY_ENTER))
    {
        if (str.length() > 0)
        {
            // Print the input string to the console
            cout << "Input: " << str << endl;
        }
    }
    else if (IsKeyPressed(KEY_BACKSPACE))
    {
        // Remove the last character from the input string
        if (str.length() > 0)
        {
            str.pop_back();

        }
    }
    else
    {
        // Get the character input from the keyboard
        int key = GetKeyPressed();
        char character = (char)key;
        str += character;
    }
}

int main()
{


    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 580;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - image loading");

    Image image = LoadImage("resources/background.png");
    Texture2D texture = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
    Vector2 Circle = { (float)70, (float)300 };
    Vector2 CircleEnemy = { (float)650, (float)300 };
    SetTargetFPS(60);     // Set our game to run at 60 frames-per-second
    Font font = LoadFont("resources/TiltWarp-Regular-VariableFont_XROT,YROT.ttf");
    bool collision = false;
    bool HasHit = false;
    int MaxCircleEnemyHP = 100;
    int CircleEnemyHP = 100;
    int MaxCircleHP = 100;
    int CircleHP = 100;
    string inputString;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (Circle.y >= 345) {
            Circle.y = 345;
        }
        if (Circle.y <= 250) {
            Circle.y = 250;
        }
        if (Circle.x >= 780) {
            Circle.x = 780;
        }
        if (Circle.x <= 20) {
            Circle.x = 20;
        }
        collision = CheckCollisionCircles(Circle, 20, CircleEnemy, 20);

        // Draw
        BeginDrawing();

        DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);

        DrawCircleV(Circle, 20, BLUE);
        DrawCircleV(CircleEnemy, 20, RED);


        if (collision == true) {
            HasHit = true;
        }
        if (HasHit) {
            Circle.x = 520;

            DrawRectangle(Circle.x - 30, Circle.y - 44, 70, 20, GRAY);
            DrawRectangle(Circle.x - 30, Circle.y - 44, (70 * CircleHP) / MaxCircleHP, 20, GREEN);
            DrawTextEx(font, to_string(CircleHP).c_str(), Vector2{ Circle.x - 10, Circle.y - 44 }, 20, 0, BLACK);

            DrawRectangle(CircleEnemy.x - 30, CircleEnemy.y - 44, 70, 20, GRAY);
            DrawRectangle(CircleEnemy.x - 30, CircleEnemy.y - 44, (70 * CircleEnemyHP) / MaxCircleEnemyHP, 20, GREEN);
            DrawTextEx(font, to_string(CircleEnemyHP).c_str(), Vector2{ CircleEnemy.x - 10, CircleEnemy.y - 44 }, 20, 0, BLACK);

            QuestionsandAnswers(inputString);
            DrawText(inputString.c_str(), 50, 50, 20, BLACK);

        }

        else if (!collision) {
            if (IsKeyDown(KEY_RIGHT)) Circle.x += .0f;
            if (IsKeyDown(KEY_LEFT)) Circle.x -= 3.0f;
            if (IsKeyDown(KEY_UP)) Circle.y -= 3.0f;
            if (IsKeyDown(KEY_DOWN)) Circle.y += 3.0f;
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