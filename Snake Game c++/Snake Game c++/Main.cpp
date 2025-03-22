#include "DoubleBuffer.h"
#include "SceneManager.h"
#include "DeleteMemory.h"
#include "Exit.h"

int main()
{
	srand((unsigned)time(NULL));//램덤한 값

	DoubleBuffer::Get()->InitBuffer();

	SceneManager::Get()->SetScene(LOGO);

	while (Exit::IsRunning())
	{
		DoubleBuffer::Get()->ClearBuffer();

		SceneManager::Get()->Update();

		DoubleBuffer::Get()->FlipBuffer();

		Sleep(16);
	}

	DoubleBuffer::Get()->CloseBuffer();
	system("cls");
	cout << "게임 종료" << endl;
	DeleteMemory deleteMemory;

	return 0;
}