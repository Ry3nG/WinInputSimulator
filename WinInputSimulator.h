#pragma once

#include "pch.h"
#include <Windows.h>
#include <string>
#include <thread>
#include <chrono>

class WinInputSimulator
{
public:
	WinInputSimulator(const std::wstring& title);
	bool activate(bool testing);
	bool press_key(WORD key, bool testing = false);
	bool move_cursor(int x, int y, bool testing = false);
	bool left_click(bool testing = false);
	bool right_click(bool testing = false);
	bool scroll(int amount, bool testing = false);

private:
	HWND window;
	std::wstring windowTitle;
	const std::chrono::milliseconds delay_between_operations;
};