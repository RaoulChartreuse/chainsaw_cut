#include <iostream>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <fstream>
using namespace std;
#include "check_dir.h"



using namespace cv;

#define CUT_VALUE 0.7



int main( int argc, char** argv ){
  if( argc != 4 ){
    printf( "Usage :\n \t * cut_file <analyse file> <video file> <output directory>  \n" );
    return -1;
  }
  // argv[0] cut
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
  vector<double> R_tab;
  double r;
  string tmp;
  int Nb_de_frame=0;
  while ( !ifs.eof()){
    ifs >> tmp;
    r=atof(tmp.c_str());
    if (isnan(r) || isinf(r)) r=0;
    R_tab.push_back(r);
    Nb_de_frame++;
  }


  // Ouvrir le fichier video
  const string videoRef = argv[2];
  VideoCapture captRefrnc(videoRef);
  if ( !captRefrnc.isOpened()){
    cout  << "Could not open reference " << videoRef << endl;
    return -1;
  }
  
  
  Mat frame, oldFrame;
  captRefrnc >> frame;

  int   index = 0;
  string out_name= make_name(p, index, ".avi");

  int ex = static_cast<int>(captRefrnc.get(CAP_PROP_FOURCC));//on utilise le meme codecs c'est un peu nul
  Size S = Size((int) captRefrnc.get(CAP_PROP_FRAME_WIDTH), 
		(int) captRefrnc.get(CAP_PROP_FRAME_HEIGHT));
  VideoWriter outputVideo;
  outputVideo.open(out_name , ex, captRefrnc.get(CAP_PROP_FPS),S, true);

  
  //Boucle  VideoWriter outputVideo;
  int i = 0;
  double n_frames = (double) captRefrnc.get( CAP_PROP_FRAME_COUNT);
  while(!frame.empty()){
    if (R_tab[i] > CUT_VALUE){
      index ++;
      outputVideo.release();
      out_name= make_name(p, index, ".avi");
      
      cout<<out_name<<"  ";
      cout<<i<<" /  "<< Nb_de_frame<< "  =  "<< 1.*i/Nb_de_frame*100<<" %              \r";
								      cout.flush();
      
      outputVideo.open(out_name , ex, captRefrnc.get(CAP_PROP_FPS),S, true);
    }
    outputVideo << frame;
    
    captRefrnc >> frame;
    i++;
  }
  outputVideo.release();

  //fin
  return 0;
}
