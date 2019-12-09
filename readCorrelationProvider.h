//
// Created by laurent on 03/12/2019.
//

#ifndef CHAINSOW_CUT_READCORRELATIONPROVIDER_H
#define CHAINSOW_CUT_READCORRELATIONPROVIDER_H


#include "CorrelationProvider.h"

class ReadCorrelationProvider : public CorrelationProvider {
private:
    std::string file;
    std::ifstream ifs;
public:
    virtual void preTraitement(cv::VideoCapture *captRef, cv::UMat &oldFrame);

    virtual void mainTraitement(cv::UMat &frame);

    virtual void postTraitement();

    ReadCorrelationProvider(std::string name, std::string filename) :
            CorrelationProvider(name), file(filename) {}
};


#endif //CHAINSOW_CUT_READCORRELATIONPROVIDER_H
