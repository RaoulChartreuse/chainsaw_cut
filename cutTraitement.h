//
// Created by laurent on 03/12/2019.
//

#ifndef CHAINSOW_CUT_CUTTRAITEMENT_H
#define CHAINSOW_CUT_CUTTRAITEMENT_H


#include <boost/filesystem/path.hpp>
#include "Traitement.h"

class CutTraitement : public Traitement {
    //heritage depuis une classe videoWriter
private :
    cv::VideoWriter outputVideo;
    std::string file;
    int ex, file_index;
    double fps;
    cv::Size S;
    boost::filesystem::path directory;

public :
    CutTraitement(std::string nom,
                  std::string description,
                  std::string filename) : Traitement(nom, description), file(filename) {}

    virtual void preTraitement(cv::VideoCapture *captRef, cv::UMat &oldFrame);

    virtual void mainTraitement(cv::UMat &frame);

    virtual void postTraitement();
};


#endif //CHAINSOW_CUT_CUTTRAITEMENT_H
