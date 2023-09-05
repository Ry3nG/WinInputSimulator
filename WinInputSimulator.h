#pragma once

#include "pch.h"
#include <Windows.h>
#include <string>
#include <thread>
#include <chrono>


enum class ErrorCode {
	SUCCESS = 0,
	WINDOW_NOT_FOUND = 1,
	FAILED_TO_ACTIVATE = 2,
	FAILED_TO_PRESS_KEY = 3,
	FAILED_TO_MOVE_CURSOR = 4,
	FAILED_TO_LEFT_CLICK = 5,
	FAILED_TO_RIGHT_CLICK = 6,
	FAILED_TO_SCROLL = 7,
	CURSOR_OUT_OF_BOUNDS = 8,
	FAILED_TO_GET_WINDOW_RECT = 9,
	FAILED_TO_SET_CURSOR_POS = 10,
	UNKNOWN_ERROR = 99,
};
class WinInputSimulator
{
public:
	WinInputSimulator(const std::wstring& title);

	// Update the return type to ErrorCode
	ErrorCode activate(bool testing);
	ErrorCode press_key(WORD key, bool testing = false);
	ErrorCode move_cursor(int x, int y, bool testing = false);
	ErrorCode left_click(bool testing = false);
	ErrorCode right_click(bool testing = false);
	ErrorCode scroll(int amount, bool testing = false);

private:
	HWND window;
	std::wstring windowTitle;
	const std::chrono::milliseconds delay_between_operations;
};