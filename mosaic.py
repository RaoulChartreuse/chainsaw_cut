# -*-coding:Latin-1 -*

import argparse
import numpy as np
import cv2
import subprocess
import os


dir = "tmp/"
row = 5
col = 6
scale = 8 #Echelle 1/2

images = os.listdir(dir)
images.sort(reverse=True)

im = cv2.imread(dir + images[0])
dx = im.shape[0] // scale
dy = im.shape[1] // scale
channel = im.shape[2]



n=0
while  len(images) >0:

    canvas = np.full( (dx*row, dy*col, channel), 255, dtype='uint8')
    for i in range(row):
        if len(images) == 0 :break
        for j in range(col):
            if len(images) == 0 :break
            im = cv2.imread(dir + images.pop())
            mini = cv2.resize(im, (dy, dx))
            canvas[i*dx:((i+1)*dx), j*dy:((j+1)*dy)] = mini
            
    
    cv2.imwrite("canvas_"+str(n)+".png", canvas)
    
    n+=1



