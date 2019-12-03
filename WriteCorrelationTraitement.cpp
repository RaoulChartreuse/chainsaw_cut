//
// Created by laurent on 03/12/2019.
//

#include "WriteCorrelationTraitement.h"

using namespace std;
using namespace cv;

void WriteCorrelationTraitement::preTraitement(cv::VideoCapture captRef, cv::UMat &oldFrame) {
    ofs = ofstream(file);
}

void WriteCorrelationTraitement::mainTraitement(cv::UMat &frame) {
    ofs << *r << " ";
}

void WriteCorrelationTraitement::postTraitement() {
    ofs.close();
}

