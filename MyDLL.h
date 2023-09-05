#pragma once

#include "WinInputSimulator.h"
#include <string>

extern "C" {
    __declspec(dllexport) bool PressKey(const wchar_t* title, WORD key);
    __declspec(dllexport) bool MoveCursor(const wchar_t* title, int x, int y);
    __declspec(dllexport) bool LeftClick(const wchar_t* title);
    __declspec(dllexport) bool RightClick(const wchar_t* title);
    __declspec(dllexport) bool Scroll(const wchar_t* title, int amount);
}