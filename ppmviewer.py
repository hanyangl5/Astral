import numpy as np
import cv2

img = cv2.imread('test/antialiasing.ppm')

cv2.imshow('image', img)
cv2.waitKey(0)#表示程序会无限制的等待用户的按键事件
cv2.destroyAllWindows()