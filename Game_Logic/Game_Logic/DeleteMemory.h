#pragma once
#include "DoubleBuffer.h"
#include "SceneManager.h"

//프로그램 종료시 포인터 해제
class DeleteMemory
{
public:
    DeleteMemory()
    {
        DoubleBuffer::Get()->DestroyPointer();
        SceneManager::Get()->DestroyPointer();
    }
};