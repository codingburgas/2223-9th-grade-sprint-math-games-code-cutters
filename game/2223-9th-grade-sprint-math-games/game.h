#pragma once
#include "raylib.h"
#include <iostream>
#include <string>
#include "endscreen.h"

int decimalToBinary(int value_1);
int IntegerCheck(int num2);
void DrawHealthBarPlayer(float x1, float y1, int health1, Font font);
void DrawHealthBarsEnemy(float x2, float y2, int health2, Font font, int bonuscordsX, int bonuscordsY);
void ShiftRight(int& number, int& value_1, int& value_2, bool& flag, int& shifter, int& health1, int& health2);
void ShiftLeft(int& number, int& value_1, int& value_2, bool& flag, int& shifter, int& health1, int& health2);
void And(int& number, int& value_1, int& value_2, bool& flag, int& shifter, int& health1, int& health2);
void Or(int& number, int& value_1, int& value_2, bool& flag, int& shifter, int& health1, int& health2);
void MoveAnimationLeft(float& timer, int& frame, int maxFrames, float frameWidth, Texture2D Run, float& x1, float& y1);
void MoveAnimationRight(float& timer, int& frame, int maxFrames, float frameWidth, Texture2D Run, float& x1, float& y1);
int game();
int endscreen();