#include <stdio.h>
#include "BoucleTraitement.h"
#include "Display.h"

int main( int argc, char** argv ){
    //Traitement des paramètres
    if( argc < 2 ){
        printf( "Usage :\n \t * analyser <videofile> <output data file> \n" );
        //return -1;
    }

    const std::string videoRef = argv[1];
    BoucleTraitement *boucle = new BoucleTraitement(videoRef);
    boucle->addTraitement( new Traitement("Vide"));
    boucle->addTraitement(new Display("Display"));
    boucle->run();

}