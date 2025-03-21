#include "SceneManager.h"
#include "Logo.h"
#include "Menu.h"
#include "Stage.h"
#include "Result.h"

SceneManager* SceneManager::instance = nullptr;

void SceneManager::SetScene(SCENE_ID id)
{
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
	}

	switch (id)
	{
	case LOGO:
		currentScene = new Logo;
		break;
	case MENU:
		currentScene = new Menu;
		break;
	case STAGE:
		currentScene = new Stage;
		break;
	case RESULT:
		currentScene = new Result;
		break;
	default:
		break;
	}
	Init();
}

void SceneManager::Init()
{
	currentScene->Init();
}

void SceneManager::Update()
{
	currentScene->Update();
}
