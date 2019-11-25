//
// Created by laurent on 25/11/2019.
//

#ifndef CHAINSOW_CUT_DISPLAY_H
#define CHAINSOW_CUT_DISPLAY_H


#include "Traitement.h"

class Display : public Traitement{

    virtual void preTraitement();
    virtual void mainTraitement(cv::UMat &frame);

public:
    Display(std::string nom) : Traitement(nom) {

    }
};


#endif //CHAINSOW_CUT_DISPLAY_H
