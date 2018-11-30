#include <iostream>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <fstream>


#include <boost/filesystem.hpp>

using namespace boost::filesystem;
using namespace std;
using namespace cv;

#define CUT_VALUE 0.7


int check_dir(path p){
  std::cout<< p << " is an empty directory ?\n";
  //Test du repertoire
  
  if(!exists(p) ) {
    printf("Invalid path \n");
    return -1;
  }

  if(!is_directory(p) ) {
    printf("Path is not a directory \n");
    return -1;
  }

  if(boost::filesystem::is_empty(p)){
    cout<< " is empty. It's all good men !"<<endl;
    return 1;
  }
  else{
    cout << p << " is a directory containing:\n";
  
    for (directory_entry& x : directory_iterator(p))
      cout<< "    " << x.path() << '\n';
      cout << "Should we delete it ?"<< endl;
      return -1;
  }
}
  
string make_name(path p, int index){
  stringstream ss;
  ss << p.string();
  ss << "out_" ;
  ss << std::setw(5) << std::setfill('0') << index;
  ss << ".avi";
  string s = ss.str();
  return s;
}

int main( int argc, char** argv ){
  if( argc != 4 ){
    printf( "Usage :\n \t * cut <analyse file> <video file> <output directory>  \n" );
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
  std::ifstream ifs(argv[2]);
  vector<double> R_tab;
  double r;
  string tmp;
  while ( !ifs.eof()){
    ifs >> tmp;
    r=atof(tmp.c_str());
    if (isnan(r)) r=0;
    R_tab.push_back(r);
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
  string out_name= make_name(p, index);

  int ex = static_cast<int>(captRefrnc.get(CAP_PROP_FOURCC));//on utilise le meme codecs c'est un peu nul
  Size S = Size((int) captRefrnc.get(CAP_PROP_FRAME_WIDTH), 
		(int) captRefrnc.get(CAP_PROP_FRAME_HEIGHT));
  VideoWriter outputVideo;
  outputVideo.open(out_name , ex, captRefrnc.get(CAP_PROP_FPS),S, true);

  
  //boucle  VideoWriter outputVideo;
  int i = 0;
  double n_frames = (double) captRefrnc.get( CAP_PROP_FRAME_COUNT);
  while(!frame.empty()){
    if (R_tab[i] > CUT_VALUE){
      index ++;
      out_name= make_name(p, index);
      outputVideo.open(out_name , ex, captRefrnc.get(CAP_PROP_FPS),S, true);
    }
    outputVideo << frame;
    
    captRefrnc >> frame;
    i++;
  }

  // -> Ecrire les fichiers
  //fin
  return 0;
}
