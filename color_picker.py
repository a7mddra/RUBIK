import numpy as np

COLOR_RANGES = {
    'orange': ((180, 95, 0), (240, 150, 130)),
    'yellow': ((145, 180, 0), (200, 230, 50)),
    'red': ((185, 26, 30), (255, 100, 130)),
    'green': ((0, 139, 0), (70, 180, 70)),
    'blue': ((0, 125, 200), (10, 160, 255)),
    'white': ((140, 195, 210), (255, 255, 255)),
}

def color_in_range(r, g, b, low, high):
    return low[0] <= r <= high[0] and low[1] <= g <= high[1] and low[2] <= b <= high[2]

def detect_color_name(r, g, b):
    for color_name, (low, high) in COLOR_RANGES.items():
        if color_in_range(r, g, b, low, high):
            return color_name
    return 'unknown'

def get_point_color(frame, x, y):
    b, g, r = frame[y, x]
    return detect_color_name(r, g, b)

def pick_color(frame, start_x, start_y, region_size=10):
    points = [
        (start_x + 25, start_y + 25),
        (start_x + region_size - 25, start_y + 25),
        (start_x + region_size - 25, start_y + region_size - 25),
        (start_x + 25, start_y + region_size - 25),
        (start_x + region_size // 2, start_y + region_size // 2),
    ]

    color_names = [get_point_color(frame, x, y) for x, y in points]

    most_frequent_color = max(set(color_names), key=color_names.count)
    return most_frequent_color
