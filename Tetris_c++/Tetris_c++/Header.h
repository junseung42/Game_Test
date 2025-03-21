#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

#define BufferWidth  200 // 가로 버퍼 크기
#define BufferHeight 200 // 세로 버퍼 크기

#define Screen_Width_Size 12//Map 가로 크기
#define Screen_Vertical_Size 21//Map 세로 크기

#define Hold_Screen_Width_Size 8//Hold_map 가로 크기
#define Hold_Screen_Vertical_Size 8//Hold_map 세로 크기

#define Next_Screen_Width_Size 8//Next_map 가로 크기
#define Next_Screen_Vertical_Size 8//Next_map 세로 크기

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