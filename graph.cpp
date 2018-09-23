#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string.h>
#include <ctime>
#include <chrono>
#include <fstream>


using namespace cv;
using namespace std;


void draw_histo(cv::Mat image, vector<double> R_tab, int index){
  int l = image.cols;
  int h = image.rows;
  //Axe Oy vertical
  cv::line( image,
	    cv::Point(l/10, h/10),
	    cv::Point(l/10, 9*h/10),
	    Scalar( 10, 10, 10),
	    2, 2, 0);
  cv::line( image,
	    cv::Point(l/10, h/10),
	    cv::Point(l/10-l/100, h/10+h/100),
	    Scalar( 10, 10, 10),
	    2, 2, 0);  
  cv::line( image,
	    cv::Point(l/10, h/10),
	    cv::Point(l/10+l/100, h/10+h/100),
	    Scalar( 10, 10, 10),
	    2, 2, 0);

  //Axe Ox horizontal
  cv::line( image,
	    cv::Point(l/10, 9*h/10),
	    cv::Point(9*l/10, 9*h/10),
	    Scalar( 10, 10, 10),
	    2, 2, 0);
  cv::line( image,
	    cv::Point(9*l/10, 9*h/10),
	    cv::Point(9*l/10-l/100, 9*h/10-h/100),
	    Scalar( 10, 10, 10),
	    2, 2, 0);  
  cv::line( image,
	    cv::Point(9*l/10, 9*h/10),
	    cv::Point(9*l/10-l/100, 9*h/10+h/100),
	    Scalar( 10, 10, 10),
	    2, 2, 0);

  //Tick horizontal
  for(int i=0; i<50; i+=10){
    
    int x= l/10 + i*(l*80./5000.);
    
    int y = 9*h/10;
    cv::line( image,
	      cv::Point(x, y),
	      cv::Point(x, y+4*h/100),
	      Scalar( 10, 10, 10),
	      2, 2, 0);    
  }
  int x= l/10 + 40*(l*8./500.);
  cv::line( image,
	    cv::Point(x, 9*h/10),
	    cv::Point(x, h/10),
	    Scalar( 10, 10, 255),
	    2, 2, 0);
  int y= 9*h/10 - 0.7*(h*8/10.);
  cv::line( image,
	    cv::Point(l/10, y),
	    cv::Point(9*l/10, y),
	    Scalar( 10, 255, 10),
	    2, 2, 0);

  
  int minus = 40;
  int plus = 10;
  int x_last=l/10;
  int y_last= 9*h/10;
  //cout<<"Boucle  : "<<R_tab.size() <<endl;
  //cout<<"Index : "<< index<< " deb : "<<max(index-minus, 0)<<", fin : "<< min(index+plus, (int)R_tab.size())<<endl;
  for(int i=max(index-minus, 0); i<(min(index+plus, (int)R_tab.size())); i++){
    x=l/10 + (i-index+minus)*(l*8./500.);
    y= 9*h/10 - R_tab[i]*(h*8/10.);
    
    cv::line( image,
	      cv::Point(x_last, y_last),
	      cv::Point(x, y),
	      Scalar( 255, 255, 10),
	      2, 2, 0);
    x_last=x;
    y_last=y;
  }

  
  
}

int main( int argc, char** argv ){

  if( argc != 4 ){
    printf( "Usage :\n \t * ReadVideo <videofile> <input data file> <outputvideo>\n" );
    return -1;
  }


  const string videoRef = argv[1];
  VideoCapture captRefrnc(videoRef);
  if ( !captRefrnc.isOpened()){
    cout  << "Could not open reference " << videoRef << endl;
    return -1;
  }

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


  VideoWriter outputVideo;
  string NAME=argv[3];
  int ex = static_cast<int>(captRefrnc.get(CAP_PROP_FOURCC));//on utilise le meme codecs c'est un peu nul
  Size S = Size((int) captRefrnc.get(CAP_PROP_FRAME_WIDTH), 
		(int) captRefrnc.get(CAP_PROP_FRAME_HEIGHT));
  outputVideo.open(NAME , ex, captRefrnc.get(CAP_PROP_FPS),S, true);


  
  Mat frame;
  captRefrnc >> frame;

  namedWindow( "graph", WINDOW_AUTOSIZE );
  int i=0;
  double n_frames = (double) captRefrnc.get( CAP_PROP_FRAME_COUNT);
  while(!frame.empty()){


    draw_histo(frame, R_tab, i);
    imshow( "graph", frame); waitKey(1);
	    

    outputVideo << frame;
    captRefrnc >> frame;
    i++;
  }
}
