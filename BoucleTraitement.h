//
// Created by laurent on 25/11/2019.
//

#ifndef CHAINSOW_CUT_BOUCLETRAITEMENT_H
#define CHAINSOW_CUT_BOUCLETRAITEMENT_H

#include <opencv2/opencv.hpp>
#include "Traitement.h"
#include <stdio.h>

class BoucleTraitement {

    std::vector<Traitement*> listeTraitement;
    cv::VideoCapture captRef;

public :
    BoucleTraitement(std::string videoRef);

    void addTraitement(Traitement *traitement);

    void run();

};


#endif //CHAINSOW_CUT_BOUCLETRAITEMENT_H
