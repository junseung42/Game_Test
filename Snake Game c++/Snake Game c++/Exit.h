#pragma once
#include "Header.h"

class Exit
{
private:
    static bool isRunning;

public:
    static void SetRunning(bool state);
    static bool IsRunning();
};