#include "Menu.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"

void Menu::Init()
{
}

void Menu::Update()
{
	DoubleBuffer::Get()->WriteBuffer(10, 10, "Menu", 10);

	if (GetAsyncKeyState(VK_RETURN))
	{
		SceneManager::Get()->SetScene(STAGE);
		Sleep(100);
	}
}
