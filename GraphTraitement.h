//
// Created by laurent on 01/12/2019.
//

#ifndef CHAINSOW_CUT_GRAPHTRAITEMENT_H
#define CHAINSOW_CUT_GRAPHTRAITEMENT_H


#include "Traitement.h"
#include <opencv2/opencv.hpp>

class GraphTraitement : public Traitement {
    // Graph thraitement à besoin du futur !!
    // -> Rustine pour pas trop modifier la structure global, on stocke 10 image
    // c'est un peu lourd !!
private :
    cv::VideoWriter outputVideo;
    static const int minus = 40; //Taille du graph avant la frame courante aucun impact memoire
    static const int plus = 10; //Nombre de frame futur !! danger ces images seront en ram
    int indexFrame;
    std::list<cv::UMat> frameBuffer;
    std::vector<double> R_tab;
    bool display = false;
    void draw_graph(int index);
    std::string file;

public:
    GraphTraitement(std::string nom, std::string description="",
            std::string filename="", bool show =false)
            : Traitement(nom, description), display(show), file(filename) {}



    virtual void preTraitement(cv::VideoCapture captRef, cv::UMat &oldFrame);
    virtual void mainTraitement(cv::UMat &frame);
    virtual void postTraitement();
};


#endif //CHAINSOW_CUT_GRAPHTRAITEMENT_H
