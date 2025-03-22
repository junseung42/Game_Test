#include "Menu.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"
#include "Exit.h"

void Menu::Init()
{
    player_y = 10;//초기값 설정
}

void Menu::Update()
{
#pragma region 화살표 움직이기
    if (GetAsyncKeyState(VK_UP)) {
        player_y -= 2;
        if (player_y <= 9) {
            player_y = 10;
        }
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        player_y += 2;
        if (player_y >= 13) {
            player_y = 12;
        }
    }
#pragma endregion
#pragma region 설명
    DoubleBuffer::Get()->WriteBuffer(20, 8, "선택 = ENTET키", 10);
    DoubleBuffer::Get()->WriteBuffer(18, player_y, "▶", 10);
    DoubleBuffer::Get()->WriteBuffer(20, 10, "START", 10);
    DoubleBuffer::Get()->WriteBuffer(20, 12, "EXIT", 10);

    //DoubleBuffer::Get()->WriteBuffer(30, 8, "조작법 -> 왼쪽으로 가기 = 왼쪽 방향키", 10);
    //DoubleBuffer::Get()->WriteBuffer(30, 10, "       -> 오른쪽으로 가기 = 오른쪽 방향키", 10);
    //DoubleBuffer::Get()->WriteBuffer(30, 12, "       -> 방향 돌리기 = 위쪽 방향키", 10);
    //DoubleBuffer::Get()->WriteBuffer(30, 14, "       -> Hold = c", 10);
    //DoubleBuffer::Get()->WriteBuffer(30, 16, "       -> 바로 내리기 = Space Bar", 10);
#pragma endregion
#pragma region 상호작용
    if (player_y == 10 && GetAsyncKeyState(VK_RETURN) & 0x8001)
    {
        SceneManager::Get()->SetScene(STAGE);
        Sleep(100);
    }
    if (player_y == 12 && GetAsyncKeyState(VK_RETURN) & 0x8001)
    {
        Exit::SetRunning(false);
        Sleep(100);
    }
#pragma endregion  
}
