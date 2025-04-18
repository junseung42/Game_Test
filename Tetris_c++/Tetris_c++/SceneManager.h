#pragma once
#include "Header.h"

class SceneManager
{

	//�̱���
private:
	static SceneManager* instance;
public:
	static SceneManager* Get()
	{
		if (instance == nullptr)
		{
			instance = new SceneManager;
		}
		return instance;
	}

	//����Scene�� ����
public:
	class Scene* currentScene = nullptr;

	//�ʱ�ȭ �� �̵��κ�
public:
	void SetScene(SCENE_ID id);
	void Init();
	void Update();

	//�̱��� ������ �����
public:
	void DestroyPointer()
	{
		delete instance;
		instance = nullptr;
		delete currentScene;
		currentScene = nullptr;
	}
};
