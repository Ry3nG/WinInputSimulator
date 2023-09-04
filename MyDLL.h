#pragma once

#include "WinInputSimulator.h"
#include <string>

extern "C" {
    __declspec(dllexport) bool MoveAndClick(const wchar_t* title, int x, int y);
    __declspec(dllexport) bool PressKey(const wchar_t* title, WORD key);
}