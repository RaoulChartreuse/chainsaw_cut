//
// Created by laurent on 01/12/2019.
//

#include "computeCorrelationProvider.h"

using namespace cv;
void ComputeCorrelationProvider::preTraitement(cv::VideoCapture captRef, cv::UMat &oldFrame) {
    Traitement::preTraitement(cv::VideoCapture(), oldFrame);
    cvtColor(oldFrame, *this->oldFrame, COLOR_BGR2GRAY);
    frame = this->oldFrame;
}

void ComputeCorrelationProvider::mainTraitement(cv::UMat &frame) {
    *r = 1. - correlation2(*oldFrame, *this->frame);
    *oldFrame = this->frame->clone();
    cvtColor(frame, *this->frame, COLOR_BGR2GRAY);
    //cvt et correlation sont lourd tout les deux, une parallelisation est possible
    //Mais il faut faire attention à frame
}

void ComputeCorrelationProvider::postTraitement() {
    Traitement::postTraitement();
}

double ComputeCorrelationProvider::correlation2(cv::UMat &im_1, cv::UMat &im_2) {
    // Compute mean and standard deviation of both images
    int n_pixels = im_1.rows * im_1.cols ;
    cv::Scalar im1_Mean, im1_Std, im2_Mean, im2_Std;
    meanStdDev(im_1, im1_Mean, im1_Std);
    meanStdDev(im_2, im2_Mean, im2_Std);

    // Compute covariance and correlation coefficient
    double correl = im_1.dot(im_2);
    correl -= n_pixels* im1_Mean[0]*im2_Mean[0];
    correl /= n_pixels*im1_Std.val[0] * im2_Std.val[0];

    return correl;
}

ComputeCorrelationProvider::ComputeCorrelationProvider(std::string name) : CorrelationProvider(name) {
    frame = 0;
}

