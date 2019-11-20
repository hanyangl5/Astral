import numpy as np
import cv2
path='test/diffuse.ppm'
img = cv2.imread(path)

cv2.namedWindow('image',cv2.WINDOW_NORMAL)
cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()