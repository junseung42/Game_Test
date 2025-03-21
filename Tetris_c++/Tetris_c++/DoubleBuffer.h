#pragma once
#include "Header.h"
class DoubleBuffer
{

	//싱글톤
private:
	static DoubleBuffer* instance;
public:
	static DoubleBuffer* Get()
	{
		if (instance == nullptr)
		{
			instance = new DoubleBuffer;
		}
		return instance;
	}

private:
	HANDLE hBuffer[2];//창 두게를 제어하는 핸들
	int screenIndex;//hBuffer[screenIndex], screenIndex == 0 or 1

	//더블버퍼 함수
public:
	void InitBuffer();//버퍼 초기화
	void FlipBuffer();//버퍼 뒤집기
	void ClearBuffer();//버퍼 깨끗이
	void WriteBuffer(int x, int y, const char* shape, int color);//버퍼 쓰기
	void CloseBuffer();//버퍼 해제

	//싱글톤 포인터 지우기
public:
	void DestroyPointer()
	{
		delete instance;
		instance = nullptr;
	}
};