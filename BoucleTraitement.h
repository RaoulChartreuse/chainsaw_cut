//
// Created by laurent on 25/11/2019.
//

#ifndef CHAINSOW_CUT_BOUCLETRAITEMENT_H
#define CHAINSOW_CUT_BOUCLETRAITEMENT_H

#include <opencv2/opencv.hpp>
#include "Traitement.h"
#include "CorrelationProvider.h"
#include <cstdio>

class BoucleTraitement {
private :
    std::vector<Traitement*> listeTraitement;
    cv::VideoCapture captRef;
    CorrelationProvider *corProvider;

public :
    explicit BoucleTraitement(std::string videoRef);

    void addTraitement(Traitement *traitement);
    void setCorrelationProvider(CorrelationProvider *provider);

    void run();

};


#endif //CHAINSOW_CUT_BOUCLETRAITEMENT_H
