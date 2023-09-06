#include "pch.h"
#include "WinInputSimulator.h"

WinInputSimulator::WinInputSimulator(const std::wstring& title)
    : windowTitle(title), delay_between_operations(10)
{
    window = nullptr;
}

ErrorCode WinInputSimulator::activate(bool testing) {
    if (testing) {
        return ErrorCode::SUCCESS;  // this is to mock the window
    }
    window = FindWindowW(NULL, windowTitle.c_str());
    if (window == nullptr) {
        return ErrorCode::WINDOW_NOT_FOUND;
    }
    if (!SetForegroundWindow(window)) {
        return ErrorCode::FAILED_TO_ACTIVATE;
    }
    return ErrorCode::SUCCESS;
}

ErrorCode WinInputSimulator::press_key(WORD key, bool testing)
{
    if (activate(testing) != ErrorCode::SUCCESS) {
        return ErrorCode::FAILED_TO_PRESS_KEY;
    }

    keybd_event(key, 0, 0, 0);
    std::this_thread::sleep_for(delay_between_operations);
    keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
    std::this_thread::sleep_for(delay_between_operations);
    return ErrorCode::SUCCESS;
}

ErrorCode WinInputSimulator::move_cursor(int x, int y, bool testing)
{
    if (activate(testing) != ErrorCode::SUCCESS) {
        return ErrorCode::FAILED_TO_MOVE_CURSOR;
    }
    RECT rect;
    if (!GetWindowRect(window, &rect)) {
        return ErrorCode::FAILED_TO_GET_WINDOW_RECT;
    }

    int new_x = rect.left + x;
    int new_y = rect.top + y;

    if (new_x < rect.left || new_x > rect.right || new_y < rect.top || new_y > rect.bottom) {
        return ErrorCode::CURSOR_OUT_OF_BOUNDS;
    }

    if (!SetCursorPos(new_x, new_y)) {
        return ErrorCode::FAILED_TO_SET_CURSOR_POS;
    }

    std::this_thread::sleep_for(delay_between_operations);
    return ErrorCode::SUCCESS;
}

ErrorCode WinInputSimulator::left_click(bool testing)
{
    if (activate(testing) != ErrorCode::SUCCESS) {
        return ErrorCode::FAILED_TO_LEFT_CLICK;
    }

    POINT pt;
    RECT rect;
    if (!GetCursorPos(&pt) || !GetWindowRect(window, &rect)) {
        return ErrorCode::FAILED_TO_GET_WINDOW_RECT;
    }

    if (pt.x < rect.left || pt.x > rect.right || pt.y < rect.top || pt.y > rect.bottom) {
        return ErrorCode::CURSOR_OUT_OF_BOUNDS;
    }

    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    std::this_thread::sleep_for(delay_between_operations);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    std::this_thread::sleep_for(delay_between_operations);

    return ErrorCode::SUCCESS;
}

ErrorCode WinInputSimulator::right_click(bool testing)
{
    if (activate(testing) != ErrorCode::SUCCESS) {
        return ErrorCode::FAILED_TO_RIGHT_CLICK;
    }

    POINT pt;
    RECT rect;
    if (!GetCursorPos(&pt) || !GetWindowRect(window, &rect)) {
        return ErrorCode::FAILED_TO_GET_WINDOW_RECT;
    }

    if (pt.x < rect.left || pt.x > rect.right || pt.y < rect.top || pt.y > rect.bottom) {
        return ErrorCode::CURSOR_OUT_OF_BOUNDS;
    }

    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    std::this_thread::sleep_for(delay_between_operations);
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    std::this_thread::sleep_for(delay_between_operations);

    return ErrorCode::SUCCESS;
}

ErrorCode WinInputSimulator::scroll(int delta, bool testing)
{
    if (activate(testing) != ErrorCode::SUCCESS) {
        return ErrorCode::FAILED_TO_SCROLL;
    }

    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, delta, 0);
    std::this_thread::sleep_for(delay_between_operations);
    return ErrorCode::SUCCESS;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    auto params = reinterpret_cast<std::pair<std::wstring, std::vector<HWND>*>*>(lParam);
    std::wstring titleSubstring = params->first;
    std::vector<HWND>* windows = params->second;

    wchar_t title[256];
    GetWindowText(hwnd, title, sizeof(title) / sizeof(wchar_t));
    std::wstring windowTitle = title;

    if (windowTitle.find(titleSubstring) != std::wstring::npos) {
        windows->push_back(hwnd);
    }
    return TRUE;
}

std::vector<HWND> WinInputSimulator::getWindowsWithTitle(const std::wstring& titleSubstring) {
    std::vector<HWND> matchingWindows;
    std::pair<std::wstring, std::vector<HWND>*> params = { titleSubstring, &matchingWindows };
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&params));
    return matchingWindows;
}
