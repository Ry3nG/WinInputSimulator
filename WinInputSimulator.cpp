#include "pch.h"
#include "WinInputSimulator.h"

WinInputSimulator::WinInputSimulator(const std::wstring& title)
	: windowTitle(title), delay_between_operations(10)
{
	window = nullptr;
}

bool WinInputSimulator::activate() {
	window = FindWindowW(NULL, windowTitle.c_str());
	if (window == nullptr) {
		return false;
	}
	SetForegroundWindow(window);
	return true;
}

bool WinInputSimulator::move_and_click(int x, int y)
{
	if (!activate()) {
		return false;
	}

	POINT pt;
	pt.x = x;
	pt.y = y;
	ClientToScreen(window, &pt);
	SetCursorPos(pt.x, pt.y);
	std::this_thread::sleep_for(delay_between_operations);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	std::this_thread::sleep_for(delay_between_operations);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	std::this_thread::sleep_for(delay_between_operations);
	return true;
}

bool WinInputSimulator::press_key(WORD key)
{
	if (!activate()) {
		return false;
	}

	keybd_event(key, 0, 0, 0);
	std::this_thread::sleep_for(delay_between_operations);
	keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
	std::this_thread::sleep_for(delay_between_operations);
	return true;
}