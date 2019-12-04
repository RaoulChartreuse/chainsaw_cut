//
// Created by laurent on 04/12/2019.
//

#ifndef CHAINSOW_CUT_MOSAICTRAITEMENT_H
#define CHAINSOW_CUT_MOSAICTRAITEMENT_H

#include <boost/filesystem/path.hpp>
#include "Traitement.h"

class MosaicTraitement : public Traitement {
    //On stock les index des frames et
    // on construit un tableau de frame à extraire
private:
    boost::filesystem::path directory;
    std::string file;
    int frameIndex, frameIndexSeuil;
    std::vector<int> indexOfMosaicFrame;
    cv::VideoCapture *cRef;

public :
    MosaicTraitement(std::string nom,
                     std::string description,
                     std::string filename) :
            Traitement(nom, description), file(filename) {
        frameIndex = 0;
        frameIndexSeuil = 0;
    }

    virtual void preTraitement(cv::VideoCapture captRef, cv::UMat &oldFrame);

    virtual void mainTraitement(cv::UMat &frame);

    virtual void postTraitement();

};


#endif //CHAINSOW_CUT_MOSAICTRAITEMENT_H
