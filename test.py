from rubik import show_rubik

w = (255, 255, 255)
r = (0, 0, 255)
b = (255, 0, 0)
o = (0, 165, 255)
g = (0, 255, 0)
y = (0, 255, 255)
mt = (0, 0, 0)

front = [[w, w, r], [b, w, o], [g, b, g]]
right = [[b, r, b], [y, b, g], [r, y, y]]
back =  [[o, y, y], [w, y, b], [g, o, b]]
left =  [[g, y, b], [r, g, o], [w, w, o]]
up =    [[r, r, y], [g, r, g], [o, o, y]]
down =  [[w, w, w], [r, o, b], [r, g, o]]

show_rubik(front, right, back, left, up, down)

