#include "Logo.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"

void Logo::Init()
{
}

void Logo::Update()//테트리스 로고 띄우기
{
	DoubleBuffer::Get()->WriteBuffer(30, 30, "Enter를 누르세요.", 10);

	if (GetAsyncKeyState(VK_RETURN) & 0x8001)
	{
		SceneManager::Get()->SetScene(MENU);
		Sleep(100);
	}
}
