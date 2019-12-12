#include <stdio.h>
#include "BoucleTraitement.h"
#include "Display.h"
#include "GraphTraitement.h"
#include "ComputeCorrelationProvider.h"
#include "WriteCorrelationTraitement.h"
#include "readCorrelationProvider.h"
#include "cutTraitement.h"
#include "mosaicTraitement.h"
#include <boost/program_options.hpp>


namespace po = boost::program_options;
using namespace std;

int main(int argc, char **argv) {

    string correlationProvider="compute";
    po::options_description generic("Generic option");
    generic.add_options()
    ("version,v", "print version string")
    ("help", "produce help message")
    ("correlationProvider,c",po::value<string>(&correlationProvider)->default_value("compute"),
                    "Correlation Provider, compute by default.\n if provided will use the file");


    string writeCorFile;
    generic.add_options()("write,w",po::value<string>(&writeCorFile) ->default_value("tmp.dat"),
            "Write correlation data to file");

    string graphFile;
    generic.add_options()("graph,g",po::value<string>(&graphFile) ->default_value("tmp.avi"),
            "Produce a graph video file") ;

    string cutDir;
    generic.add_options()("cut", po::value<string>(&cutDir) ->default_value("dir"),
            "Cut video and put it in a directory");

    generic.add_options()("display,d", "Display the video");


    string mosaicDir;
    generic.add_options()("mosaic,m", po::value<string>(&mosaicDir)->default_value("dir"),
            "Produce image in directory to be processed by mosaic.py");

    string inputFile;
    generic.add_options()("inputVideo,i", po::value<string>(&inputFile) ,
            "The analysed video");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, generic), vm);
    po::notify(vm);


    if (vm.count("inputVideo")==0) {
        cout<<"No input video !!!"<<endl;
        return 1;
    }
    if (vm.count("help")) {
        cout << generic << "\n";
        return 1;
    } else if (vm.count("version")){
        cout<< "Version 0.alpha"<< endl;
        return 1;
    }



    const std::string videoRef = argv[1];
    BoucleTraitement *boucle = new BoucleTraitement(videoRef);

    if (correlationProvider =="compute"){
        boucle->setCorrelationProvider(new ComputeCorrelationProvider("Compute"));
    }else{
        boucle->setCorrelationProvider(new ReadCorrelationProvider("ReadFile", correlationProvider));
    }

    if (vm.count("graph")) boucle->addTraitement(
            new GraphTraitement("Graph", "mon graph", graphFile, false));
    if (vm.count("write")) boucle->addTraitement(
            new WriteCorrelationTraitement("WriteR", "Description", writeCorFile));
    if (vm.count("cut")) boucle->addTraitement(
            new CutTraitement("Coupe !", "", cutDir));
    if (vm.count("display")) boucle->addTraitement(new Display("Display"));
    if (vm.count("mosaic")) boucle->addTraitement(
            new MosaicTraitement("Mosaic", "", mosaicDir));
    boucle->run();
    return 0;
}