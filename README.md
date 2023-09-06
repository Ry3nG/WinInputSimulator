# WinInputSimulator
[![Build and Test C++ DLL](https://github.com/Ry3nG/WinInputSimulator/actions/workflows/main.yml/badge.svg)](https://github.com/Ry3nG/WinInputSimulator/actions/workflows/main.yml)

WinInputSimulator us a C++ Dynamic Link Library (DLL) designed to simulate user interactions such as keyboard presses and mouse movements in Windows-based applications. This library allows you to programmatically simulate user control of mouse and keyboard, making it useful for automation tasks, testing, or other applications where manual input is not desirable or feasible. Additionally, this library can be used from Python using the `ctypes` module.


## Features

* Find windows by title substring
* Activate a window by its title
* Move the mouse cursor to a specific location within the window
* Perform left and right mouse clicks
* Scroll the mouse wheel
* Simulate key presses and releases

## Prerequisites
* Windows 10 (64-bit) or later
* Visual Studio 2019 (or later) with C++ development tools (for building the DLL)
* Python 3.8 (or later) with `ctypes` module (for using the DLL in Python)

## Installation

### From Release
1. Download the latest release from the [Releases](https://github.com/Ry3nG/WinInputSimulator/releases) page.
2. Place the DLL in a directory of your choice.

### From Source
1. Clone the repository
2. Open the solution in Visual Studio
3. Build the solution


## Usage

### API Functions
Here are the functions exported by the DLL:

```cpp
    __declspec(dllexport) ErrorCode Activate(const wchar_t* title, bool testing = false);
    __declspec(dllexport) ErrorCode PressKey(const wchar_t* title, WORD key, bool testing = false);
    __declspec(dllexport) ErrorCode MoveCursor(const wchar_t* title, int x, int y, bool testing = false);
    __declspec(dllexport) ErrorCode LeftClick(const wchar_t* title, bool testing = false);
    __declspec(dllexport) ErrorCode RightClick(const wchar_t* title, bool testing = false);
    __declspec(dllexport) ErrorCode Scroll(const wchar_t* title, int amount, bool testing = false);
    __declspec(dllexport) void GetWindowsWithTitle(const wchar_t* titleSubstring, HWND* outArray, int* outArraySize);

```
### Error Codes
The functions return an `ErrorCode` enum to indicate the result of the operation. The possible values are:

```cpp
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
```

### C++

To use the DLL in a C++ project, you can load the DLL using HMODULE and call the exported functions.

Example usage:

```cpp
    typedef bool (*MoveCursor)(const wchar_t*, int, int );

    // Load DLL
    HMODULE hModule = LoadLibrary(TEXT("./path/to/WinInputSimulator.dll"));

    // Get function Pointers
    MoveCursor moveCursor = (MoveCursor)GetProcAddress(hModule, "MoveCursor");

    // Perform actions
    moveCursor(L"Your Application", 100, 100);

    // unload the DLL
	FreeLibrary(hModule);
```

### Python

You can also use the DLL in Python using the `ctypes` module.

Example usage:

```python
import ctypes
from ctypes import cdll, c_wchar_p, c_int, c_ushort

myDLL = cdll.LoadLibrary('./path/to/WinInputSimulator.dll')

# Use the DLL's functions
press_key = myDLL.PressKey
press_key.argtypes = [c_wchar_p, c_ushort, c_int]
press_key.restype = c_int

result = press_key("Some Window Title", 65, 1)  # Simulate pressing the 'A' key
```
You can refer to the sample Python script in the repo for more examples.

## Contributing
COntributions are welcome! Feel free to open an issue or submit a pull request.

## License
[MIT](https://choosealicense.com/licenses/mit/)


