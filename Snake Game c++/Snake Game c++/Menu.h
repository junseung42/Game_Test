#pragma once
#include "Scene.h"

class Menu : public Scene
{
public:
	int player_y;//화살표의 y값 변수
public:
	virtual void Init() override;
	virtual void Update() override;
};

