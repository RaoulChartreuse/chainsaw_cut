//
// Created by laurent on 25/11/2019.
//

#include "Display.h"

using namespace cv;
void Display::preTraitement() {
    namedWindow(this->getNom(), WINDOW_AUTOSIZE);
}

void Display::mainTraitement(cv::UMat &frame) {

    imshow( this->getNom(), frame);//le nom doit rester constant
    waitKey(1);
}