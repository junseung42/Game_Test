#include "Logo.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"

void Logo::Init()
{
}

void Logo::Update()
{
	DoubleBuffer::Get()->WriteBuffer(10, 10, "Logo", 10);

	if (GetAsyncKeyState(VK_RETURN))
	{
		SceneManager::Get()->SetScene(MENU);
		
	}
}
