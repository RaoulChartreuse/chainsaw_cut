//
// Created by laurent on 25/11/2019.
//

#include <chrono>
#include "BoucleTraitement.h"
#include "CorrelationProvider.h"


using namespace cv;
using namespace std;


BoucleTraitement::BoucleTraitement(std::string videoRef) {
    captRef =cv::VideoCapture(videoRef);
}

void BoucleTraitement::addTraitement(Traitement *traitement){
    listeTraitement.push_back(traitement);
}

void BoucleTraitement::setCorrelationProvider(CorrelationProvider *provider){
    corProvider = provider;
}

void BoucleTraitement::run(){
    cv::UMat frame;
    captRef >> frame;


    auto t_debut = std::chrono::system_clock::now();
    auto t_now = std::chrono::system_clock::now();
    auto t_last = std::chrono::system_clock::now();


    cout<<"*********************************"<<endl;
    cout<<"**          Chainsaw           **"<<endl;
    cout<<"*********************************"<<endl<<endl;
    cout<<"Format de l'image :"<< frame.size()<<endl;
    int n_frames = (int) captRef.get( CAP_PROP_FRAME_COUNT);
    cout<<"Nbr de frames ="<< n_frames <<endl;


    cout<<"Coeficient de correlation : "<< corProvider->getNom()<<endl;
    cout<<endl;
    double r = 0.;
    corProvider->setRPointer(r);
    corProvider->preTraitement(&captRef, frame);
    for (auto& traitement : listeTraitement){
        traitement->setRPointer(r);
        traitement->preTraitement(&captRef, frame);
    }


    //Preembule
    cout<<endl<<"Liste des traitement"<<endl;
    for (auto& traitement : listeTraitement) {
        cout <<"  * "<< traitement->getNom() << endl;
    }
    cout<<endl;


    int i=1;
    while(!frame.empty()){
        t_now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = t_now-t_last;
        if(elapsed_seconds.count() >2){
            std::chrono::duration<double> d = t_now-t_debut;
            cout<< 1.*i/d.count()<<" fps; "
            << 100.*(float) captRef.get(CAP_PROP_POS_FRAMES )/ (1.* n_frames)
            << " %           "<<"\r";
            cout.flush();
            t_last =std::chrono::system_clock::now();
        }

        corProvider->mainTraitement(frame);
        for (auto& traitement : listeTraitement){
            traitement->mainTraitement(frame);
        }

        captRef >> frame;
        i++;

    }
    std::chrono::duration<double> dd = t_now-t_debut;
    cout<< 1.*i/dd.count()<<" fps; "
        << 100.*(float) captRef.get(CAP_PROP_POS_FRAMES )/ (1.* n_frames)
        << " %           "<<"\r";
    cout.flush();
    t_last =std::chrono::system_clock::now();


    for (auto &traitement : listeTraitement) {
        traitement->postTraitement();
    }

    cout << endl;
    t_now = std::chrono::system_clock::now();
    std::chrono::duration<double> d = t_now - t_debut;
    cout << "Duration :" << d.count() << " s" << endl;
    captRef.release();
}