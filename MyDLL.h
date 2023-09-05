#pragma once

#include "WinInputSimulator.h"
#include <string>

extern "C" {
    __declspec(dllexport) ErrorCode Activate(const wchar_t* title, bool testing = false);
    __declspec(dllexport) ErrorCode PressKey(const wchar_t* title, WORD key, bool testing = false);
    __declspec(dllexport) ErrorCode MoveCursor(const wchar_t* title, int x, int y, bool testing = false);
    __declspec(dllexport) ErrorCode LeftClick(const wchar_t* title, bool testing = false);
    __declspec(dllexport) ErrorCode RightClick(const wchar_t* title, bool testing = false);
    __declspec(dllexport) ErrorCode Scroll(const wchar_t* title, int amount, bool testing = false);
}
