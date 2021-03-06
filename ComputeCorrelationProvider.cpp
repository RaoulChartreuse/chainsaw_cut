//
// Created by laurent on 01/12/2019.
//

#include "ComputeCorrelationProvider.h"

#include <utility>

using namespace cv;
void ComputeCorrelationProvider::preTraitement(VideoCapture *captRef, cv::UMat &firstFrame) {

    cvtColor(firstFrame, oldFrame, COLOR_BGR2GRAY);
    frame = oldFrame;
}

void ComputeCorrelationProvider::mainTraitement(cv::UMat &currentFrame) {
    *r = 1. - correlation2(oldFrame, frame);
    if (isnan(*r) || isinf(*r)) *r = 0;
    oldFrame = frame.clone();
    cvtColor(currentFrame, frame, COLOR_BGR2GRAY);
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

ComputeCorrelationProvider::ComputeCorrelationProvider(std::string name) : CorrelationProvider(std::move(name)) {
    frame = 0;
}

