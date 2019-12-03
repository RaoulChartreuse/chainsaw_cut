#include <stdio.h>
#include "BoucleTraitement.h"
#include "Display.h"
#include "graphTraitement.h"
#include "computeCorrelationProvider.h"

int main( int argc, char** argv ){
    //Traitement des paramètres
    if( argc < 2 ){
        printf( "Usage :\n \t * Chainsaw <videofile> <output data file> \n" );
        //return -1;
    }

    const std::string videoRef = argv[1];
    BoucleTraitement *boucle = new BoucleTraitement(videoRef);
    boucle->setCorrelationProvider(new ComputeCorrelationProvider("Compute")
    );
    boucle->addTraitement(new GraphTraitement("Graph", "mon graph", "out.avi", false));

    boucle->run();

}