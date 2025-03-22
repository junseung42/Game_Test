#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

#define BufferWidth  200	// 가로 버퍼 크기
#define BufferHeight 200 // 세로 버퍼 크기

#define Screen_Width_Size 19//Map 가로 크기
#define Screen_Vertical_Size 19//Map 세로 크기

enum SCENE_ID
{
    LOGO,
    MENU,
    STAGE,
    RESULT,
};

enum Color
{
    Black,
    DarkBlue,
    DarkGreen,
    DarkCyan,
    DarkRed,
    DarkMagenta,
    DarkYellow,
    Gray,
    DarkGray,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Yellow,
    White,
};

enum Direction
{
    RIGHT,
    LEFT,
    UP,
    DOWN,
};