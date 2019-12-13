#include <iostream>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <fstream>
using namespace std;

#include "check_dir.h"



using namespace cv;

#define CUT_VALUE 0.7



int main( int argc, char** argv){
  if( argc != 4) {
    printf( "Usage :\n \t $ mosaic <analyse file> <video file> <output directory> \n");
    return -1;
  }
  // argv[0] mosaic
  // argv[1] analyse_file
  // argv[2] video_file
  // argv[3] p (path directory)
  
  // Verifier la presence du repertoire de sortie
  // Et le purger avec un  avertisement (POur la purge on vera plus tard TODO
  path p (argv[3]);
  int check = check_dir(  p );
  if (check == -1 ) return -1;

  
  // Ouvrir le fichier d'analyse
  std::ifstream ifs(argv[1]);
  vector<int> index;
  double r;
  int N_seuil=0;
  string tmp;
  int Nb_de_frame=0;
  while ( !ifs.eof()){
    ifs >> tmp;
    r=atof(tmp.c_str());
    if (isnan(r) || isinf(r)) r=0;

    
    if (r>CUT_VALUE) {
      /*
      cout<<"["<<N_seuil<<", "<<Nb_de_frame<<"] ; Pour r="<<r;
      cout<<" ; Delta ="<<-N_seuil+Nb_de_frame<<" ; index =";
      cout<<int((N_seuil+Nb_de_frame)/2) <<endl;*/
      index.push_back(int((N_seuil+Nb_de_frame)/2) );
      N_seuil = Nb_de_frame ;
    }
    Nb_de_frame++;
  }

  // Ouvrir le fichier video
  const string videoRef = argv[2];
  VideoCapture captRefrnc(videoRef);
  if ( !captRefrnc.isOpened()){
    cout  << "Could not open reference " << videoRef << endl;
    return -1;
  }

  Mat frame;

  for(size_t  i=0; i<index.size(); i++){
    captRefrnc.set(CAP_PROP_POS_FRAMES, index[i]);
    captRefrnc.read(frame);
    string out_name= make_name(p, i, ".png");
    imwrite(out_name, frame);
  }

  //fin
  return 0;
}
