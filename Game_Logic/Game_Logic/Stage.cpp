#include "Stage.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"

void Stage::Init()
{
}

void Stage::Update()
{
	DoubleBuffer::Get()->WriteBuffer(10, 10, "Stage", 10);
}
