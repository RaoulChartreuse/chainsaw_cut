//
// Created by laurent on 03/12/2019.
//

#include "readCorrelationProvider.h"

using namespace std;
using namespace cv;

void ReadCorrelationProvider::preTraitement(cv::VideoCapture captRef, cv::UMat &oldFrame) {
    ifs = ifstream(file);
}

void ReadCorrelationProvider::mainTraitement(cv::UMat &frame) {
    ifs >> *r;
}

void ReadCorrelationProvider::postTraitement() {
    ifs.close();
}

