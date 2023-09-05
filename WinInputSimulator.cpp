#include "pch.h"
#include "WinInputSimulator.h"

WinInputSimulator::WinInputSimulator(const std::wstring& title)
	: windowTitle(title), delay_between_operations(10)
{
	window = nullptr;
}

bool WinInputSimulator::activate(bool testing) {
	if(testing) {
		return true; // this is to mock the window
	}
	window = FindWindowW(NULL, windowTitle.c_str());
	if (window == nullptr) {
		return false;
	}
	SetForegroundWindow(window);
	return true;
}

bool WinInputSimulator::press_key(WORD key, bool testing)
{
	if (!activate(testing)) {
		return false;
	}

	keybd_event(key, 0, 0, 0);
	std::this_thread::sleep_for(delay_between_operations);
	keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
	std::this_thread::sleep_for(delay_between_operations);
	return true;
}

bool WinInputSimulator::move_cursor(int x, int y, bool testing)
{
	if (!activate(testing)) {
		return false;
	}

	POINT pt;
	GetCursorPos(&pt);
	pt.x += x;
	pt.y += y;
	SetCursorPos(pt.x, pt.y);
	std::this_thread::sleep_for(delay_between_operations);
	return true;
}

bool WinInputSimulator::left_click(bool testing)
{
	if (!activate(testing)) {
		return false;
	}

	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	std::this_thread::sleep_for(delay_between_operations);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	std::this_thread::sleep_for(delay_between_operations);
	return true;

}

bool WinInputSimulator::right_click(bool testing)
{
	if (!activate(testing)) {
		return false;
	}

	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	std::this_thread::sleep_for(delay_between_operations);
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	std::this_thread::sleep_for(delay_between_operations);
	return true;
}

bool WinInputSimulator::scroll(int delta, bool testing )
{
	if (!activate(testing)) {
		return false;
	}

	mouse_event(MOUSEEVENTF_WHEEL, 0, 0, delta, 0);
	std::this_thread::sleep_for(delay_between_operations);
	return true;
}

