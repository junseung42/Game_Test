#include "DoubleBuffer.h"
#include "SceneManager.h"
#include "DeleteMemory.h"

int main() 
{
	DoubleBuffer::Get()->InitBuffer();

	SceneManager::Get()->SetScene(LOGO);

	while (true)
	{
		DoubleBuffer::Get()->ClearBuffer();

		SceneManager::Get()->Update();
		
		DoubleBuffer::Get()->FlipBuffer();
	}

	DoubleBuffer::Get()->CloseBuffer();

	DeleteMemory deleteMemory;

	return 0;
}