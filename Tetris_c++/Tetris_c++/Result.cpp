#include "Result.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"

void Result::Init()
{
}

void Result::Update()
{
	DoubleBuffer::Get()->WriteBuffer(20, 3, "!!게임 오버!!", Red);
	DoubleBuffer::Get()->WriteBuffer(20, 5, "Enter를 누르세요.", Red);

	if (GetAsyncKeyState(VK_RETURN) & 0x8001)
	{
		SceneManager::Get()->SetScene(MENU);
	}
}
