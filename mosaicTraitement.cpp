//
// Created by laurent on 04/12/2019.
//

#include "mosaicTraitement.h"
#include "check_dir.h"

#define CUT_VALUE 0.7
using namespace std;
using namespace cv;
using namespace boost::filesystem;

void MosaicTraitement::preTraitement(cv::VideoCapture *captRef, cv::UMat &oldFrame) {
    frameIndex = 0;
    frameIndexSeuil = 0;

    directory = path(file);
    if (check_dir(directory) == -1) throw (string) "Probleme pour le repertoire de sortie";
    cRef = captRef;
}

void MosaicTraitement::mainTraitement(cv::UMat &frame) {
    if (*r > CUT_VALUE) {
        indexOfMosaicFrame.push_back(int((frameIndexSeuil + frameIndex) / 2));
        frameIndexSeuil = frameIndex;
    }
    frameIndex++;
}

void MosaicTraitement::postTraitement() {
    Mat frame;

    for (const int &i : indexOfMosaicFrame) {
        cRef->set(CAP_PROP_POS_FRAMES, i * 1.0);
        string out_name = make_name(directory, i, ".png");
        imwrite(out_name, frame);
    }
}

