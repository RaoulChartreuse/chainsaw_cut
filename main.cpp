#include <stdio.h>
#include "BoucleTraitement.h"
#include "Display.h"
#include "GraphTraitement.h"
#include "ComputeCorrelationProvider.h"
#include "WriteCorrelationTraitement.h"
#include "readCorrelationProvider.h"
#include "cutTraitement.h"
#include "mosaicTraitement.h"

int main(int argc, char **argv) {
    //Traitement des paramètres
    if (argc < 2) {
        printf("Usage :\n \t * Chainsaw <videofile> <output data file> \n");
        //return -1;
    }

    const std::string videoRef = argv[1];
    BoucleTraitement *boucle = new BoucleTraitement(videoRef);
    boucle->setCorrelationProvider(new ComputeCorrelationProvider("Compute"));
    //boucle->setCorrelationProvider(new ReadCorrelationProvider("ReadFile", "Dumbo.dat"));
    //boucle->addTraitement(new GraphTraitement("Graph", "mon graph", "out.avi", false));
    boucle->addTraitement(new WriteCorrelationTraitement("WriteR", "Description", "Dumbo.dat"));
    //boucle->addTraitement(new CutTraitement("Coupe !", "", "dir"));
    //boucle->addTraitement(new Display("Display"));
    //boucle->addTraitement(new MosaicTraitement("Mosaic", "", "dir"));
    boucle->run();

}