import copy


def flip(vec):
    for i in range(3):
        vec[i][0], vec[i][2] = vec[i][2], vec[i][0]


def transpose(vec):
    for i in range(3):
        for j in range(i + 1, 3):
            vec[i][j], vec[j][i] = vec[j][i], vec[i][j]


def f(front, up, right, down, left):
    transpose(front)
    flip(front)

    tmp = up[2][::]
    up[2][0] = left[2][2]
    up[2][1] = left[1][2]
    up[2][2] = left[0][2]

    left[0][2] = down[0][0]
    left[1][2] = down[0][1]
    left[2][2] = down[0][2]

    down[0][0] = right[2][0]
    down[0][1] = right[1][0]
    down[0][2] = right[0][0]

    right[0][0] = tmp[0]
    right[1][0] = tmp[1]
    right[2][0] = tmp[2]


def f_(left, front, up, right, down):
    flip(front)
    transpose(front)

    tmp = up[2][::]
    up[2][0] = right[0][0]
    up[2][1] = right[1][0]
    up[2][2] = right[2][0]

    right[0][0] = down[0][2]
    right[1][0] = down[0][1]
    right[2][0] = down[0][0]

    down[0][0] = left[0][2]
    down[0][1] = left[1][2]
    down[0][2] = left[2][2]

    left[0][2] = tmp[2]
    left[1][2] = tmp[1]
    left[2][2] = tmp[0]


def f2(front, up, right, down, left):
    f(front, up, right, down, left)
    f(front, up, right, down, left)


def b(back, up, right, down, left):
    transpose(back)
    flip(back)

    tmp = up[0][::]
    up[0][0] = right[0][2]
    up[0][1] = right[1][2]
    up[0][2] = right[2][2]

    right[0][2] = down[2][2]
    right[1][2] = down[2][1]
    right[2][2] = down[2][0]

    down[2][0] = left[0][0]
    down[2][1] = left[1][0]
    down[2][2] = left[2][0]

    left[0][0] = tmp[2]
    left[1][0] = tmp[1]
    left[2][0] = tmp[0]


def b_(back, up, down, right, left):
    flip(back)
    transpose(back)

    tmp = up[0][::]
    up[0][0] = left[2][0]
    up[0][1] = left[1][0]
    up[0][2] = left[0][0]

    left[0][0] = down[2][0]
    left[1][0] = down[2][1]
    left[2][0] = down[2][2]

    down[2][0] = right[2][2]
    down[2][1] = right[1][2]
    down[2][2] = right[0][2]

    right[0][2] = tmp[0]
    right[1][2] = tmp[1]
    right[2][2] = tmp[2]


def b2(back, up, right, down, left):
    b(back, up, right, down, left)
    b(back, up, right, down, left)


def l(left, up, back, down, front):
    transpose(left)
    flip(left)

    tmp = [0] * 3
    tmp[0] = up[0][0]
    tmp[1] = up[1][0]
    tmp[2] = up[2][0]

    up[0][0] = back[2][2]
    up[1][0] = back[1][2]
    up[2][0] = back[0][2]

    back[0][2] = down[2][0]
    back[1][2] = down[1][0]
    back[2][2] = down[0][0]

    down[0][0] = front[0][0]
    down[1][0] = front[1][0]
    down[2][0] = front[2][0]

    front[0][0] = tmp[0]
    front[1][0] = tmp[1]
    front[2][0] = tmp[2]


def l_(left, up, back, down, front):
    flip(left)
    transpose(left)

    tmp = [0] * 3
    tmp[0] = down[0][0]
    tmp[1] = down[1][0]
    tmp[2] = down[2][0]

    down[0][0] = back[2][2]
    down[1][0] = back[1][2]
    down[2][0] = back[0][2]

    back[0][2] = up[2][0]
    back[1][2] = up[1][0]
    back[2][2] = up[0][0]

    up[0][0] = front[0][0]
    up[1][0] = front[1][0]
    up[2][0] = front[2][0]

    front[0][0] = tmp[0]
    front[1][0] = tmp[1]
    front[2][0] = tmp[2]


def l2(left, up, back, down, front):
    l(left, up, back, down, front)
    l(left, up, back, down, front)


def r(right, up, front, down, back):
    transpose(right)
    flip(right)

    tmp = [0] * 3
    tmp[0] = up[0][2]
    tmp[1] = up[1][2]
    tmp[2] = up[2][2]

    up[0][2] = front[0][2]
    up[1][2] = front[1][2]
    up[2][2] = front[2][2]

    front[0][2] = down[0][2]
    front[1][2] = down[1][2]
    front[2][2] = down[2][2]

    down[0][2] = back[2][0]
    down[1][2] = back[1][0]
    down[2][2] = back[0][0]

    back[0][0] = tmp[2]
    back[1][0] = tmp[1]
    back[2][0] = tmp[0]


def r_(right, up, front, down, back):
    flip(right)
    transpose(right)

    tmp = [0] * 3
    tmp[0] = back[2][0]
    tmp[1] = back[1][0]
    tmp[2] = back[0][0]

    back[0][0] = down[2][2]
    back[1][0] = down[1][2]
    back[2][0] = down[0][2]

    down[0][2] = front[0][2]
    down[1][2] = front[1][2]
    down[2][2] = front[2][2]

    front[0][2] = up[0][2]
    front[1][2] = up[1][2]
    front[2][2] = up[2][2]

    up[0][2] = tmp[0]
    up[1][2] = tmp[1]
    up[2][2] = tmp[2]


def r2(right, up, front, down, back):
    r(right, up, front, down, back)
    r(right, up, front, down, back)


def u(left, front, right, back, up):
    transpose(up)
    flip(up)

    tmp = left[0][::]
    left[0][0] = front[0][0]
    left[0][1] = front[0][1]
    left[0][2] = front[0][2]

    front[0][0] = right[0][0]
    front[0][1] = right[0][1]
    front[0][2] = right[0][2]

    right[0][0] = back[0][0]
    right[0][1] = back[0][1]
    right[0][2] = back[0][2]

    back[0][0] = tmp[0]
    back[0][1] = tmp[1]
    back[0][2] = tmp[2]


def u_(left, front, right, back, up):
    flip(up)
    transpose(up)

    tmp = front[0][::]
    front[0][0] = left[0][0]
    front[0][1] = left[0][1]
    front[0][2] = left[0][2]

    left[0][0] = back[0][0]
    left[0][1] = back[0][1]
    left[0][2] = back[0][2]

    back[0][0] = right[0][0]
    back[0][1] = right[0][1]
    back[0][2] = right[0][2]

    right[0][0] = tmp[0]
    right[0][1] = tmp[1]
    right[0][2] = tmp[2]


def u2(left, front, right, back, up):
    u(left, front, right, back, up)
    u(left, front, right, back, up)


def d(down, front, left, back, right):
    transpose(down)
    flip(down)

    tmp = front[2][::]
    front[2][0] = left[2][0]
    front[2][1] = left[2][1]
    front[2][2] = left[2][2]

    left[2][0] = back[2][0]
    left[2][1] = back[2][1]
    left[2][2] = back[2][2]

    back[2][0] = right[2][0]
    back[2][1] = right[2][1]
    back[2][2] = right[2][2]

    right[2][0] = tmp[0]
    right[2][1] = tmp[1]
    right[2][2] = tmp[2]


def d_(down, front, left, back, right):
    flip(down)
    transpose(down)

    tmp = left[2][::]
    left[2][0] = front[2][0]
    left[2][1] = front[2][1]
    left[2][2] = front[2][2]

    front[2][0] = right[2][0]
    front[2][1] = right[2][1]
    front[2][2] = right[2][2]

    right[2][0] = back[2][0]
    right[2][1] = back[2][1]
    right[2][2] = back[2][2]

    back[2][0] = tmp[0]
    back[2][1] = tmp[1]
    back[2][2] = tmp[2]


def d2(down,front, left, back, right):
    d(down, front, left, back, right)
    d(down, front, left, back, right)

def print_cube(front, right, back, left, up, down):
    frontff = copy.deepcopy(front)
    rightff = copy.deepcopy(right)
    backff = copy.deepcopy(back)
    leftff = copy.deepcopy(left)
    upff = copy.deepcopy(up)
    downff = copy.deepcopy(down)
    faces = [frontff, rightff, backff, leftff, upff, downff]
    wc = (255, 255, 255)
    rc = (0, 0, 255)
    bc = (255, 0, 0)
    oc = (0, 165, 255)
    gc = (0, 255, 0)
    yc = (0, 255, 255)
    for face in faces:
        for i in range(3):
            for j in range(3):
                if face[i][j] == wc:
                    face[i][j] = "wc"
                elif face[i][j] == rc:
                    face[i][j] = "rc"
                elif face[i][j] == bc:
                    face[i][j] = "bc"
                elif face[i][j] == oc:
                    face[i][j] = "oc"
                elif face[i][j] == gc:
                    face[i][j] = "gc"
                elif face[i][j] == yc:
                    face[i][j] = "yc"

    for i in range(3):
        print("          ", end="")
        for j in range(3):
            print(upff[i][j], end=" ")
        print()
    print()

    for i in range(3):
        for j in range(3):
            print(leftff[i][j], end=" ")
        print(" ", end="")

        for j in range(3):
            print(frontff[i][j], end=" ")
        print(" ", end="")

        for j in range(3):
            print(rightff[i][j], end=" ")
        print(" ", end="")

        for j in range(3):
            print(backff[i][j], end=" ")
        print()

    print()

    for i in range(3):
        print("          ", end="")
        for j in range(3):
            print(downff[i][j], end=" ")
        print()

    print()
