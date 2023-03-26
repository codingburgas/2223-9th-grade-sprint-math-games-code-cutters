#include "raylib.h" //raylib setup
#include "game.h"

using namespace std;

//players structure
struct Player {
    float x;
    float y;
    int Health;
}player;

//enemies structure
struct Enemy {
    float x;
    float y;
    int EnemyHealth;
    bool isAlive;
}enemy;

int decimalToBinary(int value_1) {
    int binary_number = 0;
    int remainder, i = 1;

    // Until the value of n becomes 0.
    while (value_1 != 0) {
        remainder = value_1 % 2; // gets the remainder 
        binary_number += remainder * i; // 
        i = i * 10;
        value_1 = value_1 / 2;
    }

    return binary_number;
}

//Checks whether the shift operations are possible
int IntegerCheck(int num2) {
    int num1 = GetRandomValue(1, 5) * pow(2, num2);
    return num1;
}
//Draws rectangle health bars above the main character
void DrawHealthBarPlayer(float x1, float y1, int health1, Font font) {
    DrawRectangle(x1 + 35, y1 + 190, 110, 20, GRAY);
    DrawRectangle(x1 + 35, y1 + 190, (110 * health1) / 100, 20, GREEN);
    DrawTextEx(font, to_string(health1).c_str(), Vector2{ x1 + 75, y1 + 190 }, 20, 0, BLACK);
}

//Draws rectangle health bars above the enemies
void DrawHealthBarsEnemy( float x2,  float y2,  int health2, Font font, int bonuscordsX, int bonuscordsY) {
    DrawRectangle(x2 + bonuscordsX, y2 + bonuscordsY, 130, 23, GRAY); 
    DrawRectangle(x2 + bonuscordsX, y2 + bonuscordsY, (130 * health2) / 100, 23, GREEN);
    DrawTextEx(font, to_string(health2).c_str(), Vector2{ x2 + bonuscordsX + 50, y2 + bonuscordsY }, 25, 0, BLACK);
}

//Bitwise operation (shift right)
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

//Bitwise operation (shift left)
void ShiftLeft(int& number, int& value_1, int& value_2, bool& flag, int& shifter, int& health1, int& health2) {
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

//Bitwise operation (and)
void And(int& number, int& value_1, int& value_2, bool& flag, int& shifter, int& health1, int& health2) {
    int final_result = decimalToBinary((value_1 & value_2));
    cout << final_result << endl;
    if (number == final_result && flag == false) {
        health2 -= 20;
        flag = true;

        value_2 = GetRandomValue(1, 15);
        value_1 = GetRandomValue(1, 15);

        shifter++;
    }
    if (flag == false && number != 564386) {
        health1 -= 20;
        flag = true;

        value_2 = GetRandomValue(1, 15);
        value_1 = GetRandomValue(1, 15);
        shifter++;
    }
}

//Bitwise operation (or)
void Or(int& number, int& value_1, int& value_2, bool& flag, int& shifter, int& health1, int& health2) {
    int final_result = decimalToBinary((value_1 | value_2));
    cout << final_result << endl;
    if (number == final_result && flag == false) {
        health2 -= 20;
        flag = true;

        value_2 = GetRandomValue(1, 15);
        value_1 = GetRandomValue(1, 15);

        shifter++;
    }
    if (flag == false && number != 564386) {
        health1 -= 20;
        flag = true;

        value_2 = GetRandomValue(1, 15);
        value_1 = GetRandomValue(1, 15);
        shifter++;
    }
}

//Moving Animation
void MoveAnimationLeft(float& timer, int& frame, int maxFrames, float frameWidth, Texture2D Run, float& x1, float& y1) {
    timer += GetFrameTime();
    if (timer >= 0.17f) {
        timer = 0.0f;
        frame += 1;
    }

    frame = frame % maxFrames;
    DrawTextureRec(Run, Rectangle{ (frameWidth * frame), 0, frameWidth, (float)Run.width }, Vector2{ x1, y1 }, RAYWHITE);
}


int game()
{
    // Initialization
    const int screenWidth = 899;
    const int screenHeight = 580;

    player.Health = 100;
    enemy.EnemyHealth = 100;
    enemy.isAlive = true;

    bool IsInputting = false;
    bool GenerateNumbers = false; 
    bool playerspawn = false;
    bool IsFinalBossKilled = false;
    bool collision = false;
    bool HasHit = false;
    bool YouWin = false;
    bool YouLose = false;

    player.x = 0;
    player.y = 145;
    enemy.x = 480;
    enemy.y = 160;

    int shifter = 1;
    int loopcounter = 1;

    int input_number = 564386;

    string text;
    string Answer = "Your answer: " + to_string(input_number);

    Font font = LoadFont("resources/TiltWarp-Regular-VariableFont_XROT,YROT.ttf");

    Image image = LoadImage("resources/background.png");
    Texture2D texture = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    Texture2D player1 = LoadTexture("resources/runA.png");
    Texture2D playerBackwards = LoadTexture("resources/runB.png");
    Texture2D enemy1 = LoadTexture("resources/enemy.png");
    Texture2D list = LoadTexture("resources/scroll.png");
    Texture2D portal = LoadTexture("resources/protal.png");
    Texture2D enemy2 = LoadTexture("resources/enemy2.png");

    int value_2 = GetRandomValue(1, 5);
    int value_1 = IntegerCheck(value_2);

    float frameWidthPlayer = (float)(player1.width / 8);
    float frameWidthEnemy = (float)(enemy1.width / 8)  + 2;
    float frameWidthEnemy2 = (float)(enemy2.width / 8  + 6);
    float frameWidthPortal = (float)(portal.width / 9 - 3);
    int maxFramesPlayer = (int)(player1.width / (int)frameWidthPlayer);
    int maxFramesEnemy = (int)(enemy1.width / (int)frameWidthEnemy);
    int maxFramesEnemy2 = (int)(enemy2.width / (int)frameWidthEnemy2);
    int maxFramesPortal = (int)(portal.width / (int)frameWidthPortal);
    float timer = 0.0f;
    float timer2 = 0.0f;
    int framePlayer = 0;
    int frameEnemy = 0;
    int frameEnemy2 = 0;
    int framePortal = 0;
    
    SetTargetFPS(60);     // Set our game to run at 60 frames-per-second

    Rectangle playerRec = { player.x, player.y, float(player1.width / 8), float(player1.height)  };
    Rectangle enemyRec = { 520, 200, float(enemy1.width), float(enemy1.height) };
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //barriers and a loop counter for the levels
        if (player.x <= -115.0f)
            player.x = -115.0f;
        else if (player.x >= 715.0f) {
            player.x = -115.0f;
            loopcounter++;
            enemy.isAlive = true;
            enemy.EnemyHealth = 100;
        }
        
        //changes the hitbox of the second enemy
        if (loopcounter == 2) {
            enemyRec = { 380, 280, float(enemy2.width), float(enemy2.height) };
        }

        collision = false;

        //collision checking
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

        //Draws the player and the background
        DrawRectangle(player.x, player.y, (player1.width / 8), player1.height, WHITE);
        DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);
        DrawTextureRec(player1, Rectangle{ (frameWidthPlayer * framePlayer), 0, frameWidthPlayer, (float)player1.width }, Vector2{ player.x, player.y }, RAYWHITE);
        
        //First enemy idle animation
        if (enemy.isAlive == true && loopcounter == 1) {
            timer += GetFrameTime();
            if (timer >= 0.17f) {
                timer = 0.0f;
                frameEnemy += 1;
            }

            frameEnemy = frameEnemy% maxFramesEnemy;
            DrawTextureRec(enemy1, Rectangle{ (frameWidthEnemy * frameEnemy), 0, frameWidthEnemy, (float)player1.width }, Vector2{ enemy.x, enemy.y }, RAYWHITE);
        }
        //Second enemy idle animation
        if (enemy.isAlive == true && loopcounter == 2) {
            enemy.x = 650;
            enemy.y = 320;
            timer2 += GetFrameTime();
            if (timer2 >= 0.23f) {
                timer2 = 0.0f;
                frameEnemy2 += 1;
            }
            frameEnemy2 = frameEnemy2 % maxFramesEnemy2;
            DrawTextureRec(enemy2, Rectangle{ (frameWidthEnemy2 * frameEnemy2), 0, frameWidthEnemy2, (float)player1.width }, Vector2{ 380 , -200}, RAYWHITE);
        }
        if (collision) {
            HasHit = true;
        }
        //First level fight
        if (HasHit == true && loopcounter == 1) {
            MoveAnimationLeft(timer, framePlayer, maxFramesPlayer, frameWidthPlayer, player1, player.x, player.y);
            player.x = 315;

            //Draws the health bars
            DrawHealthBarPlayer(player.x, player.y, player.Health, font);
            DrawHealthBarsEnemy(enemy.x, enemy.y + 180, enemy.EnemyHealth, font, 0, 0);
            
            //a shifter is alternating and if its an even number the operation will be (Shift right) or if its odd the operation will be (Shift left) it will show it on the list
            if (shifter % 2 != 0) {
                text = "What is " + to_string(value_1) + " >> " + to_string(value_2) + "?";
            }
            else {
                text = "What is " + to_string(value_1) + " << " + to_string(value_2) + "?";
            }

            //draw the list and the question on it
            DrawTexture(list, 230, 20, RAYWHITE);
            DrawText(text.c_str(), 290, 95, 31, BLACK);

            //gets the input from the console
            if (IsKeyPressed('R')) {
                cin >> input_number;
                IsInputting = false;
            }

            if (IsKeyPressed('X')) {
                enemy.EnemyHealth -= 100;
            }
            if (input_number != 564386) {
                Answer = "Your answer: " + to_string(input_number);
                DrawText(Answer.c_str(), 290, 130, 30, BLACK);
            }
            //a shifter is alternating and if its an even number the operation will be (Shift right) or if its odd the operation will be (Shift left)
            if (shifter % 2 != 0) {
                ShiftRight(input_number, value_1, value_2, IsInputting, shifter, player.Health, enemy.EnemyHealth);
            }
            else {
                ShiftLeft(input_number, value_1, value_2, IsInputting, shifter, player.Health, enemy.EnemyHealth);
            }
            //checks if the enemy is dead
            if (enemy.EnemyHealth <= 0 && loopcounter == 1) {
                UnloadTexture(enemy1);
                if (player.Health != 100) {
                    player.Health += 20; //Heals after the level
                }
                HasHit = false;
                collision = false;
                enemy.isAlive = false;

                shifter = 0;
                enemy.EnemyHealth = 100;
                ClearBackground(RAYWHITE);
                shifter = 1;
            }
            //checks if the player is dead
            if (player.Health <= 0) {
                UnloadTexture(player1);
                HasHit = false;
                YouLose = true;
                YouWin = false;
                endscreen(YouWin, YouLose);
                CloseAudioDevice();
                UnloadTexture(texture);
                exit(0);
            }
        }
        
        //Second level
        else if (HasHit == true && loopcounter == 2) {
            MoveAnimationLeft(timer, framePlayer, maxFramesPlayer, frameWidthPlayer, player1, player.x, player.y);
            player.x = 220;
            //Draws health bars (made out of rectangles)
            DrawHealthBarPlayer(player.x, player.y, player.Health, font);
            DrawHealthBarsEnemy(enemy.x - 110, enemy.y - 45, enemy.EnemyHealth, font, 0, 0);

            //Change the numbers so that we dont use the last ones twice
            if (!GenerateNumbers) {
                value_1 = GetRandomValue(1, 15);
                value_2 = GetRandomValue(1, 15);
                GenerateNumbers = true;
            }
            //a shifter is alternating and if its an even number the operation will be (AND) or if its odd the operation will be (OR) it will show it on the list
            if(shifter % 2 != 0) {
                text = "What is " + to_string(decimalToBinary(value_1)) + " & " + to_string(decimalToBinary(value_2)) + "?";
            }
            else{
                text = "What is " + to_string(decimalToBinary(value_1)) + " | " + to_string(decimalToBinary(value_2)) + "?";
            }

            //draw the list and the question on it
            DrawTexture(list, 230, 20, RAYWHITE);
            DrawText(text.c_str(), 290, 95, 31, BLACK);

            //gets the input from the console
            if (IsKeyPressed('R')) {
                cin >> input_number;
                IsInputting = false;
            }
            if (IsKeyPressed('X')) {
                enemy.EnemyHealth -= 100;
            }
            
            if (input_number != 564386) {
                Answer = "Your answer: " + to_string(input_number);
                DrawText(Answer.c_str(), 290, 130, 30, BLACK);
            }
            //a shifter is alternating and if its an even number the operation will be (AND) or if its odd the operation will be (OR)
            if (shifter % 2 != 0) {
                And(input_number, value_1, value_2, IsInputting, shifter, player.Health, enemy.EnemyHealth);
            }
            else {
                Or(input_number, value_1, value_2, IsInputting, shifter, player.Health, enemy.EnemyHealth);
            }
            //checks if the enemy is dead
            if (enemy.EnemyHealth <= 0 && loopcounter == 2) {
                UnloadTexture(enemy2);

                HasHit = false;
                collision = false;
                enemy.isAlive = false;
                shifter = 0;
                IsFinalBossKilled = true;
                
            }
            //checks if the player is dead
            if (player.Health <= 0) {
                UnloadTexture(player1);
                HasHit = false;
                YouWin = false;
                YouLose = true;
                endscreen(YouWin, YouLose);
                CloseAudioDevice();
                UnloadTexture(texture);
                exit(0);
            }
        }
        
        //If the final boss has been killed, a portal will be drawn
        if (IsFinalBossKilled) {
            timer2 += GetFrameTime();
            if (timer2 >= 0.23f) {
                timer2 = 0.0f;
                framePortal += 1;
            }
            framePortal = framePortal % maxFramesPortal;
            DrawTextureRec(portal, Rectangle{ (frameWidthPortal * framePortal), 0, frameWidthPortal, (float)portal.width }, Vector2{ 525 , 110 }, RAYWHITE);
            //goes to the end screen if you pass through the portal's coordinates
            if (player.x >= 490) {
                YouWin = true;
                YouLose = false;
                endscreen(YouWin, YouLose);
                CloseAudioDevice();
                UnloadTexture(texture);
                exit(0);
            }
        }

        //Controls and animation
        if (!HasHit) {
            if (IsKeyDown('D')) {
                player.x += 3.0f;
                MoveAnimationLeft(timer, framePlayer, maxFramesPlayer, frameWidthPlayer, player1, player.x, player.y);
            }
            else if (IsKeyDown('A')) {
                player.x -= 3.0f;
                MoveAnimationLeft(timer, framePlayer, maxFramesPlayer, frameWidthPlayer, player1, player.x, player.y);
            }
            else {
                DrawTextureRec(player1, Rectangle{ (frameWidthPlayer * framePlayer), 0, frameWidthPlayer, (float)player1.width }, Vector2{ player.x, player.y }, RAYWHITE);
            }
        }


        EndDrawing();
    }

    UnloadTexture(texture);       // Texture unloading

    return 0;
}