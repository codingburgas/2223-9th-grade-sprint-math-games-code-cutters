#include "raylib.h" //raylib setup
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
    bool isAlive;
}Enemy;

//void ToggleFullscreenWindow() {
//    if (IsKeyPressed('F')) {
//        int MonitorSize = GetCurrentMonitor();
//        SetWindowSize(GetMonitorWidth(MonitorSize), GetMonitorHeight(MonitorSize));
//        ToggleFullscreen();
//    }
//}

int IntegerCheck(int num2) {
    int num1 = GetRandomValue(1, 5) * pow(2, num2);
    return num1;
}

void DrawHealthBarPlayer(float x1, float y1, int health1, Font font) {
    DrawRectangle(x1 + 35, y1 + 190, 110, 20, GRAY);
    DrawRectangle(x1 + 35, y1 + 190, (110 * health1) / 100, 20, GREEN);
    DrawTextEx(font, to_string(health1).c_str(), Vector2{ x1 + 75, y1 + 190 }, 20, 0, BLACK);
}

void DrawHealthBarsEnemy( float x2,  float y2,  int health2, Font font, int bonuscordsX, int bonuscordsY) {
    DrawRectangle(x2 + bonuscordsX, y2 + bonuscordsY, 130, 23, GRAY); //315 100
    DrawRectangle(x2 + bonuscordsX, y2 + bonuscordsY, (130 * health2) / 100, 23, GREEN);
    DrawTextEx(font, to_string(health2).c_str(), Vector2{ x2 + bonuscordsX + 50, y2 + bonuscordsY }, 25, 0, BLACK);
}


void ShiftRight(int& number, int& value_1, int& value_2, bool& flag, int& shifter, int& health1, int& health2) {
    if (number == (value_1 >> value_2) && flag == false) {
        health2 -= 20;
        flag = true;

        value_2 = GetRandomValue(1, 5);
        value_1 = IntegerCheck(value_2);
        shifter++;
    }
    if (flag == false && number != 564386) {
        health1 -= 20;
        flag = true;

        value_2 = GetRandomValue(1, 5);
        value_1 = GetRandomValue(10, 30);
    }
}

void ShiftLeft(int number, int value_1, int value_2, bool flag, int shifter, int health1, int health2) {
    if (number == (value_1 << value_2) && flag == false) {
        health2 -= 20;
        flag = true;

        value_2 = GetRandomValue(1, 5);
        value_1 = IntegerCheck(value_2);
        shifter++;
    }
    if (flag == false && number != 564386) {
        health1 -= 20;
        flag = true;

        value_2 = GetRandomValue(1, 5);
        value_1 = GetRandomValue(10, 30);
    }
}

void MoveAnimationLeft(float& timer, int& frame, int maxFrames, float frameWidth, Texture2D Run, float& x1, float& y1) {
    timer += GetFrameTime();
    if (timer >= 0.17f) {
        timer = 0.0f;
        frame += 1;
    }

    frame = frame % maxFrames;
    DrawTextureRec(Run, Rectangle{ (frameWidth * frame), 0, frameWidth, (float)Run.width }, Vector2{ x1, y1 }, RAYWHITE);
}

void MoveAnimationRight(float& timer, int& frame, int maxFrames, float frameWidth, Texture2D Run, float& x1, float& y1) {
    timer += GetFrameTime();
    if (timer >= 0.17f) {
        timer = 0.0f;
        frame += 1;
    }

    frame = frame % maxFrames;
    DrawTextureRec(Run, Rectangle{ (frameWidth * frame), 0, frameWidth, (float)Run.width }, Vector2{ x1, y1 }, RAYWHITE);
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 880;
    const int screenHeight = 580;

    static Player player;
    static Enemy enemy;

    player.Health = 100;
    enemy.EnemyHealth = 100;

    bool flag = false;
    bool playerspawn = false;
    bool CharacterFacing = false;
    enemy.isAlive = true;
    bool collision = false;
    bool HasHit = false;

    player.x = 0;
    player.y = 140;
    enemy.x = 600;
    enemy.y = 145;

    int shifter = 1;
    int loopcounter = 1;

    int input_number = 564386;

    string text;
    string Answer = "Your answer: " + to_string(input_number);

    InitWindow(screenWidth, screenHeight, "CodeCutters");

    Font font = LoadFont("resources/TiltWarp-Regular-VariableFont_XROT,YROT.ttf");

    static Image image = LoadImage("resources/background.png");
    static Texture2D texture = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    static Texture2D player1 = LoadTexture("resources/runA.png");
    static Texture2D playerBackwards = LoadTexture("resources/runB.png");
    static Texture2D enemy1 = LoadTexture("resources/enemy.png");
    static Texture2D list = LoadTexture("resources/scroll.png");
    static Texture2D enemy2 = LoadTexture("resources/enemy2.png");

    int value_2 = GetRandomValue(1, 5);
    int value_1 = IntegerCheck(value_2);

    float frameWidthPlayer = (float)(player1.width / 8);
    float frameWidthEnemy = (float)(enemy1.width / 8)  + 2;
    int maxFramesPlayer = (int)(player1.width / (int)frameWidthPlayer);
    int maxFramesEnemy = (int)(enemy1.width / (int)frameWidthEnemy);
    float timer = 0.0f;
    int framePlayer = 0;
    int frameEnemy = 0;
    

    SetTargetFPS(60);     // Set our game to run at 60 frames-per-second


    Rectangle playerRec = { player.x, player.y, float(player1.width / 8), float(player1.height)  };
    Rectangle enemyRec = { 750, 400, float(enemy1.width), float(enemy1.height) };
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        

        if (player.x <= -115.0f)
            player.x = -115.0f;
        if (player.x >= 715.0f) {
            player.x = -115.0f;
            loopcounter++;
            enemy.isAlive = true;
            enemy.EnemyHealth = 100;
        }
 
        if (loopcounter == 2) {
            enemyRec = { 780, 280, float(enemy2.width), float(enemy2.height) };
        }

        collision = false;

        if (enemy.isAlive) {
            playerRec = { player.x, player.y, float(player1.width / 8), float(player1.height) };
            if (loopcounter == 1) {
                collision = CheckCollisionRecs(playerRec, enemyRec);
            }
            else {
                collision = CheckCollisionRecs(playerRec, enemyRec);
            }
            
        }


        // Draw
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(player.x, player.y, (player1.width / 8), player1.height, WHITE);
        DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);
        DrawTextureRec(player1, Rectangle{ (frameWidthPlayer * framePlayer), 0, frameWidthPlayer, (float)player1.width }, Vector2{ player.x, player.y }, RAYWHITE);
        
        
        if (enemy.isAlive == true && loopcounter == 1) {
            timer += GetFrameTime();
            if (timer >= 0.17f) {
                timer = 0.0f;
                frameEnemy += 1;
            }

            frameEnemy = frameEnemy% maxFramesEnemy;
            DrawTextureRec(enemy1, Rectangle{ (frameWidthEnemy * frameEnemy), 0, frameWidthEnemy, (float)player1.width }, Vector2{ enemy.x, enemy.y }, RAYWHITE);
        }
        if (enemy.isAlive == true && loopcounter == 2) {
            enemy.x = 650;
            enemy.y = 320;
            DrawTexture(enemy2, enemy.x, enemy.y, WHITE);

        }
       
        if (collision) {
            HasHit = true;
        }
        if (HasHit) {
            MoveAnimationLeft(timer, framePlayer, maxFramesPlayer, frameWidthPlayer, player1, player.x, player.y);
            player.x = 400;
            if (loopcounter == 1) {
                DrawHealthBarPlayer(player.x, player.y, player.Health, font);
                DrawHealthBarsEnemy(enemy.x, enemy.y + 180, enemy.EnemyHealth, font, 0, 0);
            }
            else {
                DrawHealthBarPlayer(player.x, player.y, player.Health, font);
                DrawHealthBarsEnemy(enemy.x + 10, enemy.y - 20, enemy.EnemyHealth, font, 0, 0);
                cout << enemy.EnemyHealth;
            }
            

            if (shifter % 2 != 0) {
                text = "What is " + to_string(value_1) + " >> " + to_string(value_2) + "?";
            }
            else {
                text = "What is " + to_string(value_1) + " << " + to_string(value_2) + "?";
            }

            DrawTexture(list, 160, 100, RAYWHITE);
            DrawText(text.c_str(), 220, 175, 34, BLACK);


            if (IsKeyPressed('R')) {
                cin >> input_number;
                flag = false;
            }
            if (IsKeyPressed('X')) {
                enemy.EnemyHealth -= 100;
            }
            if (input_number != 564386) {
                Answer = "Your answer: " + to_string(input_number);
                DrawText(Answer.c_str(), 220, 210, 32, BLACK);
            }
            if (shifter % 2 != 0) {
                ShiftRight(input_number, value_1, value_2, flag, shifter, player.Health, enemy.EnemyHealth);
            }
            else {
                ShiftLeft(input_number, value_1, value_2, flag, shifter, player.Health, enemy.EnemyHealth);

            }
            if (enemy.EnemyHealth == 0 && loopcounter == 1) {
                UnloadTexture(enemy1);
                if (player.Health != 100) {
                    player.Health += 20; //Heals after a level
                }
                HasHit = false;
                collision = false;
                enemy.isAlive = false;

                shifter = 0;
                enemy.EnemyHealth = 100;
                ClearBackground(RAYWHITE);
            }
            if (enemy.EnemyHealth == 0 && loopcounter == 2) {
                UnloadTexture(enemy2);
                if (player.Health != 100) {
                    player.Health += 20; //Heals after a level
                }
                HasHit = false;
                collision = false;
                enemy.isAlive = false;

                shifter = 0;
                ClearBackground(RAYWHITE);
            }
            if (player.Health == 0) {
                UnloadTexture(player1);
                HasHit = false;
                CloseWindow();
            }
        }

        else if (!collision) {
            if (IsKeyDown('D')) {
                player.x += 3.0f;
                MoveAnimationLeft(timer, framePlayer, maxFramesPlayer, frameWidthPlayer, player1, player.x, player.y);
                CharacterFacing = true;
            }
            else if (IsKeyDown('A')) {
                player.x -= 3.0f;
                MoveAnimationRight(timer, framePlayer, maxFramesPlayer, frameWidthPlayer, playerBackwards, player.x, player.y);
                CharacterFacing = false;
            }
            else {
                DrawTextureRec(player1, Rectangle{ (frameWidthPlayer * framePlayer), 0, frameWidthPlayer, (float)player1.width }, Vector2{ player.x, player.y }, RAYWHITE);
            }
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