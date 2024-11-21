import cv2
import numpy as np

def show_rectangle_with_color(picked_color):
    picked_color = tuple(int(c) for c in picked_color)
    height, width = 480, 640
    image = np.zeros((height, width, 3), dtype=np.uint8)
    rect_width, rect_height = 200, 100
    top_left = ((width - rect_width) // 2, (height - rect_height) // 2)
    bottom_right = (top_left[0] + rect_width, top_left[1] + rect_height)

    current_color = picked_color
    red_color = (0, 0, 255)

    while True:
        image[:] = 0  # Clear the image
        cv2.rectangle(image, top_left, bottom_right, current_color, -1)
        cv2.imshow("Color Rectangle", image)

        key = cv2.waitKey(1) & 0xFF
        if key == ord('r'):
            current_color = red_color if current_color != red_color else picked_color
        elif key == ord('q') or key == 27:  # Press 'q' or 'ESC' to quit
            break

    cv2.destroyAllWindows()
