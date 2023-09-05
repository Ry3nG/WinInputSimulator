import unittest
from ctypes import cdll, c_wchar_p, c_int, c_ushort

# load DLL
myDLL = cdll.LoadLibrary('./x64/Release/WinInputSimulator.dll')
if not myDLL:
    raise Exception("Could not load DLL")
else:
    print("DLL loaded")

class TestWinInputSimulator(unittest.TestCase):
    SUCCESS = 0  # Assuming the "success" error code is 0

    def test_press_key(self):
        press_key = myDLL.PressKey
        press_key.argtypes = [c_wchar_p, c_ushort, c_int]
        press_key.restype = c_int

        result = press_key("Some Window Title", 65, 1)
        self.assertEqual(result, self.SUCCESS)

    def test_move_cursor(self):
        move_cursor = myDLL.MoveCursor
        move_cursor.argtypes = [c_wchar_p, c_int, c_int, c_int]
        move_cursor.restype = c_int

        result = move_cursor("Some Window Title", 100, 100, 1)
        self.assertEqual(result, self.SUCCESS)

    def test_left_click(self):
        left_click = myDLL.LeftClick
        left_click.argtypes = [c_wchar_p, c_int]
        left_click.restype = c_int

        result = left_click("Some Window Title", 1)
        self.assertEqual(result, self.SUCCESS)

    def test_right_click(self):
        right_click = myDLL.RightClick
        right_click.argtypes = [c_wchar_p, c_int]
        right_click.restype = c_int

        result = right_click("Some Window Title", 1)
        self.assertEqual(result, self.SUCCESS)
    
    def test_scroll(self):
        scroll = myDLL.Scroll
        scroll.argtypes = [c_wchar_p, c_int, c_int]
        scroll.restype = c_int

        result = scroll("Some Window Title", 3, 1)
        self.assertEqual(result, self.SUCCESS)

if __name__ == '__main__':
    unittest.main()
