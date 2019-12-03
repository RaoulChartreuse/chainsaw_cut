//
// Created by laurent on 01/12/2019.
//

#ifndef CHAINSOW_CUT_COMPUTECORRELATIONPROVIDER_H
#define CHAINSOW_CUT_COMPUTECORRELATIONPROVIDER_H


#include <opencv2/core/mat.hpp>
#include "CorrelationProvider.h"

class ComputeCorrelationProvider: public CorrelationProvider {
private:
    cv::UMat *oldFrame;
    cv::UMat *frame;
    double correlation2(cv::UMat &im_1, cv::UMat &im_2);
public:
    virtual void preTraitement(cv::VideoCapture captRef, cv::UMat &oldFrame);
    virtual void mainTraitement(cv::UMat &frame);
    virtual void postTraitement();

    ComputeCorrelationProvider(std::string name);
};


#endif //CHAINSOW_CUT_COMPUTECORRELATIONPROVIDER_H
