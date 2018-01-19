from collections import deque
import numpy as np
import cv2
import sys
import imutils
import time

print(sys.argv)

colors = [[(45, 57, 210), (86, 255, 255), (0, 255, 0)],
          [(76, 176, 208), (130, 255, 255), (255, 0, 0)],
          [(0, 176, 223), (10, 255, 255), (0, 0, 255)],
          [(130, 100, 201), (165, 255, 255), (0, 0, 0)]]

low = (130, 102, 214)
high = (161, 255, 255)
points = deque(maxlen=50000)
camera = cv2.VideoCapture(sys.argv[1])
r=0

while True:
    print(r)
    (grabbed, frame) = camera.read()
    r += 1
    frame = imutils.resize(frame, width=500)
    if r == 140:
        cv2.imwrite("140.png", frame)
    if r == 240:
        cv2.imwrite("240.png", frame)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    data = []
    for color in colors:
        mask = cv2.inRange(hsv, color[0], color[1])
        mask = cv2.erode(mask, None, iterations=1)
        mask = cv2.dilate(mask, None, iterations=2)
        cv2.imshow("Frame", mask)

        cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
        center = None
        x, y, radius = 0, 0, 0
        if len(cnts) > 0:
            c = max(cnts, key=cv2.contourArea)
            ((x, y), radius) = cv2.minEnclosingCircle(c)
            M = cv2.moments(c)
            center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
#            if radius > 10:
#                cv2.circle(frame, (int(x), int(y)), int(radius), color[2], 5)
#                cv2.circle(frame, center, 5, color[2], -1)
        points.appendleft(center)
        thickness = -1
        for i in range(1, len(points)):
            if points[i - 1] is None or points[i] is None:
                continue
            thickness = int(np.sqrt(50000 / float(i+1)) * 2.5)
        data.append((x, y, color, radius, thickness, center))
    for d in data:
        ok = True
        print(d)
        if d[0] == 0 and d[1] == 0 and d[4] == -1:
            continue
        for d2 in data:
            if d == d2:
                continue
            minr = min(d[3], d2[3])
            maxr = max(d[3], d2[3])
            dx = abs(d[0]-d2[0])
            dy = abs(d[1]-d2[1])
            print(maxr, dx, dy)
            if maxr * maxr * 1.2 > dx * dx + dy * dy and d[3] < d2[3]:
                ok = False
                continue
        if d[3] > 10 and ok:
            print("k")
            cv2.circle(frame, (int(d[0]), int(d[1])), int(d[3]), d[2][2], 5)
            cv2.circle(frame, d[5], 5, d[2][2], -1)
    print("l")
    if len(sys.argv) > 2:
        cv2.imshow("Frame", frame)
    key = cv2.waitKey(1) & 0xFF

    if key == ord("q"):
        break
camera.release()
cv2.destroyAllWindows()
