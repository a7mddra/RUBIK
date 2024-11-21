from rubik_moves import *
from ui import *
import kociemba
import numpy as np

wc = (255, 255, 255)
rc = (0, 0, 255)
bc = (255, 0, 0)
oc = (0, 165, 255)
gc = (0, 255, 0)
yc = (0, 255, 255)
mt = (0, 0, 0)

def str_cube(faces):
    cube = ""
    for f in faces:
        for i in range(3):
            for j in range(3):
                if f[i][j] == wc:
                    cube += 'F'
                elif f[i][j] == bc:
                    cube += 'R'
                elif f[i][j] == yc:
                    cube += 'B'
                elif f[i][j] == gc:
                    cube += 'L'
                elif f[i][j] == oc:
                    cube += 'D'
                elif f[i][j] == rc:
                    cube += 'U'
                else:
                    cube += 'e'
    return cube

def solve(cube):
    sol = kociemba.solve(cube)
    return sol


def show_rubik(frontf, rightf, backf, leftf, upf, downf):
    h, w = 480+210, 640+280
    image = np.full((h, w, 3), (22, 22, 22), dtype=np.uint8)
    top_left = (485+50, 50+50)
    bottom_right = (850-50, 200-50)
    text = ""
    front = copy.deepcopy(frontf)
    right = copy.deepcopy(rightf)
    back = copy.deepcopy(backf)
    left = copy.deepcopy(leftf)
    up = copy.deepcopy(upf)
    down = copy.deepcopy(downf)

    faces = [up, right, front, down, left, back]

    sol = solve(str_cube(faces))

    sol = sol.split()

    face_size = 3 * (w // 14 + (w // 14 // 8))
    Y = int(h / 2 - 0.5 * face_size)
    X = int(w / 2 - face_size)

    step = 0
    while True:
        faces_list = [
            (front, (X, Y)),
            (right, (X + face_size, Y)),
            (back, (X + 2*face_size, Y)),
            (up, (X, Y - face_size)),
            (down, (X, Y + face_size)),
            (left, (X - face_size, Y)),
        ]
        for face, (pos_x, pos_y) in faces_list:
            draw_rubik_face(image, pos_x, pos_y, face)

        key = cv2.waitKey(1) & 0xFF
        if key == ord('r'):
            if step < len(sol):
                move = sol[step]
            else: move = "unknown"
            if move == "R'":
                r_(right, up, front, down, back)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "R":
                r(right, up, front, down, back)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "R2":
                r2(right, up, front, down, back)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "L'":
                l_(left, up, back, down, front)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "L":
                l(left, up, back, down, front)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "L2":
                l2(left, up, back, down, front)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "D'":
                d_(down, front, left, back, right)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "D":
                d(down, front, left, back, right)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "D2":
                d2(down,front, left, back, right)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "U'":
                u_(left, front, right, back, up)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "U":
                u(left, front, right, back, up)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "U2":
                u2(left, front, right, back, up)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "F'":
                f_(left, front, up, right, down)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "F":
                f(front, up, right, down, left)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "F2":
                f2(front, up, right, down, left)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "B'":
                b_(back, up, down, right, left)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "B":
                b(back, up, right, down, left)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            elif move == "B2":
                b2(back, up, right, down, left)
                text = move
                print(move)
                print_cube(front, right, back, left, up, down)
            step += 1
        image_with_text = customize_text(image, text, top_left, bottom_right, color=gc)
        if key == ord('c'):
            text = "Solved"
        elif key == ord('q') or key == 27:
            break
        cv2.imshow("Rubik's Cube Solver By A7MD", image_with_text)

    cv2.destroyAllWindows()
