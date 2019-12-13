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

    string correlationProvider = "compute";
    po::options_description generic("Generic option");
    generic.add_options()
            ("version,v", "print version string")
            ("help", "produce help message")
            ("correlationProvider,c", po::value<string>(&correlationProvider)->default_value("compute"),
             "Correlation Provider, compute by default.\n if provided will use the file");


    string writeCorFile;
    generic.add_options()("write,w", po::value<string>(&writeCorFile),
                          "Write correlation data to file");

    string graphFile;
    generic.add_options()("graph,g", po::value<string>(&graphFile),
                          "Produce a graph video file");

    string cutDir;
    generic.add_options()("cut", po::value<string>(&cutDir),
                          "Cut video and put it in a directory");

    generic.add_options()("display,d", "Display the video");


    string mosaicDir;
    generic.add_options()("mosaic,m", po::value<string>(&mosaicDir),
                          "Produce image in directory to be processed by mosaic.py");

    string inputFile;
    generic.add_options()("inputVideo,i", po::value<string>(&inputFile),
                          "The analysed video");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, generic), vm);
    po::notify(vm);


    if (vm.count("inputVideo") == 0) {
        cout << "No input video !!!" << endl;
        return 1;
    }
    if (vm.count("help")) {
        cout << generic << "\n";
        return 1;
    } else if (vm.count("version")) {
        cout << "Version 0.alpha" << endl;
        return 1;
    }



    //const std::string videoRef = argv[1];
    auto *boucle = new BoucleTraitement(inputFile);

    if (correlationProvider == "compute") {
        boucle->setCorrelationProvider(new ComputeCorrelationProvider("Compute"));
    } else {
        boucle->setCorrelationProvider(new ReadCorrelationProvider("ReadFile", correlationProvider));
    }

    if (vm.count("graph")) {
        boucle->addTraitement(
                new GraphTraitement("Graph", "mon graph", graphFile, false));
    }
    if (vm.count("write")) {
        boucle->addTraitement(
                new WriteCorrelationTraitement("WriteR", "Description", writeCorFile));
        cout << "Write treatment added" << endl;
    }
    if (vm.count("cut")) {
        boucle->addTraitement(
                new CutTraitement("Coupe !", "", cutDir));
        cout << "Cut treatment added, destination directory"<< cutDir << endl;
    }
    if (vm.count("display")) {
        boucle->addTraitement(new Display("Display"));
        cout << "Display treatment added" << endl;
    }
    if (vm.count("mosaic")){
        boucle->addTraitement(
                new MosaicTraitement("Mosaic", "", mosaicDir));
        cout<<"Mosaic treatment added, destination directory"<< mosaicDir <<endl;
}
    boucle->run();
    return 0;
}