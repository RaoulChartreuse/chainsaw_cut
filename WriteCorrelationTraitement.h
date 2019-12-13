//
// Created by laurent on 03/12/2019.
//

#ifndef CHAINSOW_CUT_WRITECORRELATIONTRAITEMENT_H
#define CHAINSOW_CUT_WRITECORRELATIONTRAITEMENT_H


#include "Traitement.h"

class WriteCorrelationTraitement : public Traitement {
private :
    std::string file;
    std::ofstream ofs;

public:
    WriteCorrelationTraitement(std::string nom, std::string description = "",
                               std::string filename = "")
            : Traitement(nom, description), file(filename) {}


    virtual void preTraitement(cv::VideoCapture *captRef, cv::UMat &oldFrame);

    virtual void mainTraitement(cv::UMat &frame);

    virtual void postTraitement();


};


#endif //CHAINSOW_CUT_WRITECORRELATIONTRAITEMENT_H
