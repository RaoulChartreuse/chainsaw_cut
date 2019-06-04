# -*-coding:Latin-1 -*

import argparse
import numpy as np
import cv2
import subprocess
import os


ap = argparse.ArgumentParser()

ap.add_argument("-d", "--directory", required = True,
                help = "Repertoire")
ap.add_argument("-p", "--prefix", required = False,
                help = "Repertoire", default="canvas_")
ap.add_argument("-s", "--scale", required = False,
                help = "Echelle", default=8)
args = ap.parse_args()
dir = args.directory
row = 5
col = 6
scale = args.scale #Echelle 1/2
prefix = args.prefix


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
            
    
    cv2.imwrite(prefix+str(n)+".png", canvas)
    
    n+=1



