//
// Created by laurent on 25/11/2019.
//

#ifndef CHAINSOW_CUT_TRAITEMENT_H
#define CHAINSOW_CUT_TRAITEMENT_H

#include <opencv2/opencv.hpp>

class Traitement {

    std::string nom;
    std::string description;

public :
    Traitement(std::string nom){
    this->nom = nom;
}

Traitement(std::string nom, std::string description){
    this->nom = nom;
    this->description = description;
}

    virtual void preTraitement();
    virtual void mainTraitement(cv::UMat &frame);
    virtual void postTraitement();

    void setNom(std::string nom){ this->nom = nom ;}
    std::string getNom(){return nom;}
    void setDescription(std::string description){
        this->description = description; ;}
    std::string getDescription() {return description;}


};


#endif //CHAINSOW_CUT_TRAITEMENT_H
