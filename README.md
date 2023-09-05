# WinInputSimulator
[![Build and Test C++ DLL](https://github.com/Ry3nG/WinInputSimulator/actions/workflows/main.yml/badge.svg)](https://github.com/Ry3nG/WinInputSimulator/actions/workflows/main.yml)

A C++ DLL for simulating keyboard and mouse input in Windows applications.

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Requirements](#requirements)
4. [Installation](#installation)
5. [Usage](#usage)


## Introduction

WinInputSimulator is a C++ DLL designed to simulate user interactions such as keyboard presses and mouse movements in Windows-based applications. It can be used in automated testing frameworks, bots, or any other context where user simulation is required.

## Features

- **Keyboard Simulation:** Simulate any keypresses including special keys.
- **Mouse Simulation:** Simulate mouse movement, left-clicks, right-clicks, and scrolling.
- **Window Targeting:** Direct input simulation to specific application windows.
- **Customization:** Fine-grain control over delay between input events.

## Requirements

- Windows 10 or higher.
- Visual Studio 2019 or later.
- Python 3.x for running Python tests.

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/Ry3nG/WinInputSimulator.git
    ```
2. Open `WinInputSimulator.sln` with Visual Studio.
3. Build the solution (Ctrl+Shift+B).

## Usage

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


