import cv2

def customize_text(image, text, top_left, bottom_right, font=cv2.FONT_HERSHEY_SIMPLEX, color=(0, 0, 0), thickness=4):

    region_width = bottom_right[0] - top_left[0]
    region_height = bottom_right[1] - top_left[1]

    font_scale = 1

    while True:
        text_size = cv2.getTextSize(text, font, font_scale, thickness)[0]
        if text_size[0] <= region_width and text_size[1] <= region_height:
            font_scale += 0.1
        else:
            font_scale -= 0.1
            break

    text_size = cv2.getTextSize(text, font, font_scale, thickness)[0]
    text_x = top_left[0] + (region_width - text_size[0]) // 2
    text_y = top_left[1] + (region_height + text_size[1]) // 2
    cv2.rectangle(image, (top_left[0]-10, top_left[1]-10), (bottom_right[0]+10, bottom_right[1]+10), (22, 22, 22), -1)
    cv2.putText(image, text, (text_x, text_y), font, font_scale, color, thickness)

    return image

def draw_rubik_face(img, x, y, colors):
    square_size = img.shape[1] // 14
    padding = square_size // 8
    for i in range(3):
        for j in range(3):
            X = x + j * (square_size + padding)
            Y = y + i * (square_size + padding)
            cv2.rectangle(img, (X, Y), (X + square_size, Y + square_size), colors[i][j], -1)

def draw_face(img, minX, minY, offset, square, colors):
    for i in range(3):
        for f in range(3):
            X = minX + f * (square + offset)
            Y = minY + i * (square + offset)
            cv2.rectangle(img, (X, Y), (X + square, Y + square), colors[i][f], -1)