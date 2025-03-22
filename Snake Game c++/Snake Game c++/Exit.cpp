#include "Exit.h"

// 정적 변수 초기화
bool Exit::isRunning = true;

// 실행 여부 설정
void Exit::SetRunning(bool state)
{
    isRunning = state;
}

// 실행 여부 반환
bool Exit::IsRunning()
{
    return isRunning;
}