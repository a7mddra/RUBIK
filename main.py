import cv2
import numpy as np
import mediapipe as mp
from camera_controller import correct_droidcam_feed
from color_picker import pick_color
from rubik import show_rubik
from ui import draw_face

mp_hands = mp.solutions.hands
hands = mp_hands.Hands(min_detection_confidence=0.5, min_tracking_confidence=0.5)
mp_draw = mp.solutions.drawing_utils

cap = cv2.VideoCapture(2)

w, h = 640, 480
frame = np.zeros((h, w, 3), dtype=np.uint8)



wc = (255, 255, 255)
rc = (0, 0, 255)
bc = (255, 0, 0)
oc = (0, 165, 255)
gc = (0, 255, 0)
yc = (0, 255, 255)
mt = (0, 0, 0)

front = [[mt, mt, mt], [mt, wc, mt], [mt, mt, mt]]
right = [[mt, mt, mt], [mt, bc, mt], [mt, mt, mt]]
back =  [[mt, mt, mt], [mt, yc, mt], [mt, mt, mt]]
left =  [[mt, mt, mt], [mt, gc, mt], [mt, mt, mt]]
up =    [[mt, mt, mt], [mt, rc, mt], [mt, mt, mt]]
down =  [[mt, mt, mt], [mt, oc, mt], [mt, mt, mt]]

faces = [front, right, back, left, up, down]

xx = 290
yy = 190
xxx = 685
yyy = 595
rg = int((((xxx-xx)/3)+((yyy-yy)/3))/2)
off = 5
positions = [
    (xx, yy), (xx+off+rg, yy), (xx+2*off+2*rg, yy),
    (xx, yy+off+rg), (xx+2*off+2*rg, yy+off+rg),
    (xx, yy+2*off+2*rg), (xx+off+rg, yy+2*off+2*rg), (xx+2*off+2*rg, yy+2*off+2*rg)
]

isPicked = [False, False, False, False, False, False]

current_face = 0


w, h = correct_droidcam_feed(
    cap, width_scale=0.8, height_scale=1.0
)

w += 350
h += 280

while True:
    ret, frame = cap.read()
    frame = cv2.resize(frame, (w, h))
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    result = hands.process(rgb_frame)

    if result.multi_hand_landmarks:
        for hand_landmarks in result.multi_hand_landmarks:
            mp_draw.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

    padding = w // 64
    sqSize = padding * 3
    faceSize = padding * 12
    leftX = int(w // 6.4 * 0.44)
    rightX = w - (faceSize + leftX)
    topY = int(h // 4.8 * 0.44)
    bottomY = h - (faceSize + topY)


    draw_face(frame, leftX, int(topY), padding, sqSize, front)
    draw_face(frame, leftX, int(h / 2 - 0.5 * faceSize), padding, sqSize, right)
    draw_face(frame, leftX, int(bottomY), padding, sqSize, back)
    draw_face(frame, rightX, int(topY), padding, sqSize, left)
    draw_face(frame, rightX, int(h / 2 - 0.5 * faceSize), padding, sqSize, up)
    draw_face(frame, rightX, int(bottomY), padding, sqSize, down)


    if not isPicked[current_face]:
        for j, pos in enumerate(positions):
            color = mt
            detected_color = pick_color(frame, pos[0], pos[1], rg)

            if detected_color == "white":
                color = wc
            elif detected_color == "blue":
                color = bc
            elif detected_color == "yellow":
                color = yc
            elif detected_color == "green":
                color = gc
            elif detected_color == "red":
                color = rc
            elif detected_color == "orange":
                color = oc

            t = j
            if j >= 4:
                t += 1

            row = t // 3
            col = t % 3

            faces[current_face][row][col] = color

    lineLX = int(1.5*leftX) + faceSize
    lineTY = topY + int(0.5*faceSize)
    thickness = padding // 2
    lineBY = bottomY + int(0.5*faceSize)
    lineRX = w - lineLX - thickness
    cv2.rectangle(frame, (lineLX, lineTY), (lineLX + thickness, lineBY), (0, 0, 0), -1)
    cv2.rectangle(frame, (lineLX, lineBY), (lineRX, lineBY + thickness), (0, 0, 0), -1)

    cv2.imshow("Rubik Detection", frame)

    key = cv2.waitKey(1) & 0xFF

    if key == ord("r"):
        isPicked[current_face] = True

        if current_face < 5:
            current_face += 1

    if key == ord("g"):
        current_face -= 1
        isPicked[current_face] = False

        if current_face < 0:
            current_face = 0

    if isPicked[5]:
        cv2.destroyAllWindows()
        show_rubik(front, right, back, left, up, down)

    if key == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
