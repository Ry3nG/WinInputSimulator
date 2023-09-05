#include "pch.h"
#include "MyDLL.h"

extern "C" {

    __declspec(dllexport) bool PressKey(const wchar_t* title, WORD key) {
        WinInputSimulator controller = WinInputSimulator(std::wstring(title));

        if (!controller.activate()) {
            return false;
        }

        return controller.press_key(key);
    }

    __declspec(dllexport) bool MoveCursor(const wchar_t* title, int x, int y) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (!controller.activate()) {
			return false;
		}

		return controller.move_cursor(x, y);
	}

    __declspec(dllexport) bool LeftClick(const wchar_t* title) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (!controller.activate()) {
			return false;
		}

		return controller.left_click();
	}

	__declspec(dllexport) bool RightClick(const wchar_t* title) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (!controller.activate()) {
			return false;
		}
		return controller.right_click();
	}

	__declspec(dllexport) bool Scroll(const wchar_t* title, int amount) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (!controller.activate()) {
			return false;
		}
		return controller.scroll(amount);
	}
}
