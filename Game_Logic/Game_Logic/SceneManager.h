#pragma once
#include "Header.h"

class SceneManager
{

//싱글톤
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

//현재Scene의 상태
public:
	class Scene* currentScene = nullptr;

//초기화 및 이동부분
public:
	void SetScene(SCENE_ID id);
	void Init();
	void Update();

//싱글톤 포인터 지우기
public:
	void DestroyPointer()
	{
		delete instance;
		instance = nullptr;
	}
};
