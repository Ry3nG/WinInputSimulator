#include "pch.h"
#include "MyDLL.h"

extern "C" {
    __declspec(dllexport) bool MoveAndClick(const wchar_t* title, int x, int y) {
        WinInputSimulator controller = WinInputSimulator(std::wstring(title));

        if (!controller.activate()) {
            return false;
        }

        return controller.move_and_click(x, y);
    }

    __declspec(dllexport) bool PressKey(const wchar_t* title, WORD key) {
        WinInputSimulator controller = WinInputSimulator(std::wstring(title));

        if (!controller.activate()) {
            return false;
        }

        return controller.press_key(key);
    }
}
