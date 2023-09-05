#include "pch.h"
#include "MyDLL.h"

extern "C" {

    __declspec(dllexport) bool PressKey(const wchar_t* title, WORD key, bool testing) {
        WinInputSimulator controller = WinInputSimulator(std::wstring(title));

        if (!controller.activate(testing)) {
            return false;
        }

        return controller.press_key(key,testing);
    }

    __declspec(dllexport) bool MoveCursor(const wchar_t* title, int x, int y, bool testing) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (!controller.activate(testing)) {
			return false;
		}

		return controller.move_cursor(x, y,testing);
	}

    __declspec(dllexport) bool LeftClick(const wchar_t* title, bool testing ) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (!controller.activate(testing)) {
			return false;
		}

		return controller.left_click(testing);
	}

	__declspec(dllexport) bool RightClick(const wchar_t* title, bool testing) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (!controller.activate(testing)) {
			return false;
		}
		return controller.right_click(testing);
	}

	__declspec(dllexport) bool Scroll(const wchar_t* title, int amount, bool testing) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (!controller.activate(testing)) {
			return false;
		}
		return controller.scroll(amount,testing);
	}
}
