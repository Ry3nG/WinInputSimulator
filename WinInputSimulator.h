#pragma once
#include <Windows.h>
#include <string>
#include <thread>
#include <chrono>

class WinInputSimulator
{
public:
	WinInputSimulator(const std::wstring& title);
	bool activate();
	bool move_and_click(int x, int y);
	bool press_key(WORD key);

private:
	HWND window;
	std::wstring windowTitle;
	const std::chrono::milliseconds delay_between_operations;
};