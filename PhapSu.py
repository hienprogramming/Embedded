import pyautogui
import math
import time

def move_mouse_in_circle(radius, center_x, center_y):
    while True:
        for degree in range(0, 360, 5):
            angle = math.radians(degree)
            x = center_x + radius * math.cos(angle)
            y = center_y + radius * math.sin(angle)
            pyautogui.moveTo(x, y, duration=0.01)

# Thiết lập bán kính và tâm
radius = 100
center_x, center_y = pyautogui.size()[0] // 2, pyautogui.size()[1] // 2

# Chạy mãi mãi
move_mouse_in_circle(radius, center_x, center_y)
