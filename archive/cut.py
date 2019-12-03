# -*-coding:Latin-1 -*

"""
Cut est problmatique, il ne fait le cedoupage qu'entre les keys frames.
C'est plutot rapide mais le resultat n'est pas frame perfect.
"""
import argparse
import cv2
import numpy as np
import subprocess

ap = argparse.ArgumentParser()
ap.add_argument("-i", "--input", required = True,
                help = "Chemin vers le tableau")
ap.add_argument("-v", "--video", required = True,
                help = "Chemin vers le fichier video")
ap.add_argument("-o", "--output", required = True,
                help = "output directory")
ap.add_argument("-c", "--cut", default=0.7,
                help = "The cut value")
args = ap.parse_args()
video = args.video
input = args.input
output = args.output

R = args.cut
print R
r = np.loadtxt(input)

cap = cv2.VideoCapture(video)
#frame_width = int(cap.get(3))
#frame_height = int(cap.get(4))
frame_rate = cap.get(5)
print "fr :", frame_rate

i = 0
last = 0
cut = []
while i< r.size :
    if r[i]> R and i-last>4:
        print i/frame_rate, " ", last/frame_rate, "dt = ", (i - last)/frame_rate
        cut.append([last/frame_rate, i/frame_rate])
        last = i
    i+=1
print len(cut)

i=0
for t in cut :
    # ffmpeg -ss 4200 -t 00:00:30 -i /media/Vidéos/Whipl.avi -c copy tmp.avi
    print "ffmpeg -ss", t[0],"-t", t[1]-t[0], "-i", input, "-c copy", output+"/%03d.avi"%i
    a = subprocess.call(["ffmpeg","-y",
                         "-loglevel", "panic",
                         "-ss", str(t[0]),
                         "-t", str(t[1]-t[0]),
                         "-i", video,
                         #"-c",  "copy",
                         "-c:a", "libmp3lame",
                         output+"/%03d.mp3"%i])
    print i, " over ", len(cut), "\r"
    i+=1



