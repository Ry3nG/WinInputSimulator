from ctypes import cdll, c_wchar_p, c_int, c_ushort
import time

class WinInputSimulator():
    # Error Codes
    SUCCESS = 0
    WINDOW_NOT_FOUND = 1
    FAILED_TO_ACTIVATE = 2
    FAILED_TO_PRESS_KEY = 3
    FAILED_TO_MOVE_CURSOR = 4
    FAILED_TO_LEFT_CLICK = 5
    FAILED_TO_RIGHT_CLICK = 6
    FAILED_TO_SCROLL = 7
    CURSOR_OUT_OF_BOUNDS = 8
    FAILED_TO_GET_WINDOW_RECT = 9
    FAILED_TO_SET_CURSOR_POS = 10
    UNKNOWN_ERROR = 99
    # (Add all your other error codes here)

    WINDOW_TITLE = "Document - WordPad"  # Target window title
    
    def __init__(self):
        self.myDLL = cdll.LoadLibrary('./x64/Debug/WinInputSimulator.dll')
        if not self.myDLL:
            raise Exception("Could not load DLL")
        else:
            print("DLL loaded")

        self.activate = self.myDLL.Activate
        self.activate.argtypes = [c_wchar_p, c_int]
        self.activate.restype = c_int

        self.press_key = self.myDLL.PressKey
        self.press_key.argtypes = [c_wchar_p, c_ushort, c_int]
        self.press_key.restype = c_int

        self.move_cursor = self.myDLL.MoveCursor
        self.move_cursor.argtypes = [c_wchar_p, c_int, c_int, c_int]
        self.move_cursor.restype = c_int

        self.left_click = self.myDLL.LeftClick
        self.left_click.argtypes = [c_wchar_p, c_int]
        self.left_click.restype = c_int

# Create an instance of the class
simulator = WinInputSimulator()

# Test the functions
activation_status = simulator.activate(c_wchar_p(WinInputSimulator.WINDOW_TITLE), c_int(0))
if activation_status == WinInputSimulator.SUCCESS:
    print("Activated window")
else:
    print(activation_status)

move_status = simulator.move_cursor(c_wchar_p(WinInputSimulator.WINDOW_TITLE), c_int(100), c_int(100), c_int(0))
if move_status == WinInputSimulator.SUCCESS:
    print("Cursor moved")
else:
    print(move_status)


click_status = simulator.left_click(c_wchar_p(WinInputSimulator.WINDOW_TITLE), c_int(0))
if click_status == WinInputSimulator.SUCCESS:
    print("Left click successful")
else:
    print(click_status)

press_status = simulator.press_key(c_wchar_p(WinInputSimulator.WINDOW_TITLE), c_ushort(65), c_int(0))  # Assuming 'A'
if press_status == WinInputSimulator.SUCCESS:
    print("Key press successful")
else:
    print(press_status)
