#include "pch.h"
#include "MyDLL.h"

extern "C" {

	__declspec(dllexport) ErrorCode Activate(const wchar_t* title, bool testing) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));
		return controller.activate(testing);
	}

	__declspec(dllexport) ErrorCode PressKey(const wchar_t* title, WORD key, bool testing) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (controller.activate(testing) != ErrorCode::SUCCESS) {
			return ErrorCode::FAILED_TO_PRESS_KEY;
		}

		return controller.press_key(key, testing);
	}

	__declspec(dllexport) ErrorCode MoveCursor(const wchar_t* title, int x, int y, bool testing) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (controller.activate(testing) != ErrorCode::SUCCESS) {
			return ErrorCode::FAILED_TO_MOVE_CURSOR;
		}

		return controller.move_cursor(x, y, testing);
	}

	__declspec(dllexport) ErrorCode LeftClick(const wchar_t* title, bool testing) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (controller.activate(testing) != ErrorCode::SUCCESS) {
			return ErrorCode::FAILED_TO_LEFT_CLICK;
		}

		return controller.left_click(testing);
	}

	__declspec(dllexport) ErrorCode RightClick(const wchar_t* title, bool testing) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (controller.activate(testing) != ErrorCode::SUCCESS) {
			return ErrorCode::FAILED_TO_RIGHT_CLICK;
		}
		return controller.right_click(testing);
	}

	__declspec(dllexport) ErrorCode Scroll(const wchar_t* title, int amount, bool testing) {
		WinInputSimulator controller = WinInputSimulator(std::wstring(title));

		if (controller.activate(testing) != ErrorCode::SUCCESS) {
			return ErrorCode::FAILED_TO_SCROLL;
		}
		return controller.scroll(amount, testing);
	}
	__declspec(dllexport) void GetWindowsWithTitle(const wchar_t* titleSubstring, HWND* outArray, int* outArraySize) {
		std::vector<HWND> windows = WinInputSimulator::getWindowsWithTitle(std::wstring(titleSubstring));
		int size = static_cast<int>(windows.size());
		if (size > *outArraySize) {
			size = *outArraySize;
		}
		for (int i = 0; i < size; ++i) {
			outArray[i] = windows[i];
		}
		*outArraySize = size;
	}
}