#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{


    // Initialization
    const int screenWidth = 900;
    const int screenHeight = 580;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - image loading");

    Font font = LoadFont("resources/TiltWarp-Regular-VariableFont_XROT,YROT.ttf");
 

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        EndDrawing();
    }

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}