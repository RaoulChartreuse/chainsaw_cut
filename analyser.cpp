#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string.h>
#include <math.h>
#include <ctime>
#include <chrono>
#include <fstream>


using namespace cv;
using namespace std;

double correlation2(cv::Mat &image_1, cv::Mat &image_2)   {
  Mat grey1, grey2;
  cvtColor(image_1, grey1, COLOR_BGR2GRAY);
  cvtColor(image_2, grey2, COLOR_BGR2GRAY);

  // convert data-type to "float"
  cv::Mat im_float_1;
  grey1.convertTo(im_float_1, CV_32F);
  cv::Mat im_float_2;
  grey2.convertTo(im_float_2, CV_32F);

  int n_pixels = grey1.rows * grey1.cols ;
  // Compute mean and standard deviation of both images
  cv::Scalar im1_Mean, im1_Std, im2_Mean, im2_Std;
  meanStdDev(im_float_1, im1_Mean, im1_Std);
  meanStdDev(im_float_2, im2_Mean, im2_Std);

  // Compute covariance and correlation coefficient
  im_float_1 = im_float_1 - im1_Mean;
  double covar = im_float_1.dot(im_float_2 - im2_Mean) / n_pixels;
  double correl = covar / (im1_Std.val[0] * im2_Std.val[0]);

  return correl;
}

double correlation4(cv::Mat &image_1, cv::Mat &image_2)   {
  Mat grey1, grey2;
  return 4.3;
}

float correlation(cv::Mat &image1, cv::Mat &image2)
{
  Mat covar, mean;
  Mat grey1, grey2;
  cvtColor(image1, grey1, COLOR_BGR2GRAY);
  cvtColor(image2, grey2, COLOR_BGR2GRAY);
  Mat d[] =  {grey1.reshape(1,1), grey2.reshape(1,1)};
  cv::calcCovarMatrix 	( d,
			  2,
			  covar,
			  mean,
			  COVAR_NORMAL//| CV_COVAR_COLS//? |CV_COVAR_ROWS
			  );

 cout<< covar << endl;
 return 12.3;
}


float correlation3(cv::Mat &image1, cv::Mat &image2){
  Mat covar, mean, result;
  Mat grey1, grey2;
  cvtColor(image1, grey1, COLOR_BGR2GRAY);
  cvtColor(image2, grey2, COLOR_BGR2GRAY);
  grey1.convertTo(grey1, CV_32F, 1.0/255.0);
  grey2.convertTo(grey2, CV_32F, 1.0/255.0);
  cv::matchTemplate(grey1, grey2, result, TM_CCORR_NORMED );


  return result.at<float>(0,0);
}


double cov_correlation(Mat image1, Mat image2){
  Mat grey1, grey2;
  cvtColor(image1, grey1, COLOR_BGR2GRAY);
  cvtColor(image2, grey2, COLOR_BGR2GRAY);

  Mat G_image1, G_image2, RESULT;
  grey1.convertTo(grey1, CV_32FC1);
  grey2.convertTo(grey2, CV_32FC1);//, 1.0/255.0);

    //FORWARD TRANSFORMS
  dft(grey1, G_image1);
  dft(grey2, G_image2);

  //MULTIPLY CONJUGATE
  mulSpectrums(G_image1,G_image2,G_image1,true);

  //BACKWARD TRANSFORM
  dft(G_image1,RESULT);

  Scalar s = sum(RESULT);
  return  s.val[0];
}


int main( int argc, char** argv ){

  if( argc != 3 ){
    printf( "Usage :\n \t * analyser <videofile> <output data file> \n" );
    return -1;
  }

  const string videoRef = argv[1];
  VideoCapture captRefrnc(videoRef);
  if ( !captRefrnc.isOpened()){
    cout  << "Could not open reference " << videoRef << endl;
    return -1;
  }


  
  ofstream ofs(argv[2]);

  Mat frame, oldFrame;
  captRefrnc >> oldFrame;
  frame = oldFrame;
  namedWindow( "analyser", WINDOW_AUTOSIZE );


  auto t_debut = std::chrono::system_clock::now();
  auto t_now = std::chrono::system_clock::now();
  auto t_last = std::chrono::system_clock::now();

  int i=1;
  cout<< frame.size()<<endl;
  int n_frames = (int) captRefrnc.get( CAP_PROP_FRAME_COUNT);
  cout<<"Nbr de frames ="<< n_frames <<endl;

  while(!frame.empty()){

    imshow( "analyser", frame);


    double R=1-correlation2(oldFrame, frame);
    //cout<<i<<" : " << R<<endl;
    t_now = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = t_now-t_last;
    if(elapsed_seconds.count() >2){
      std::chrono::duration<double> d = t_now-t_debut;
      cout<< 1.*i/d.count()<<" fps; "<< 100.*(float) captRefrnc.get(CAP_PROP_POS_FRAMES )/ (1.* n_frames)<< " %           "<<"\r";
      cout.flush();
      t_last =std::chrono::system_clock::now();

      
    }

    ofs << R<<" ";
    if(R>0.7){
      waitKey(1);
    }
	     //  cout << 1- correlation2(oldFrame, frame);

    i++;


	    oldFrame = frame.clone();

    captRefrnc >> frame;
  }
  ofs.close();
  cout<<endl;
  t_now = std::chrono::system_clock::now();
  std::chrono::duration<double> d = t_now-t_debut;
  cout<<"Duration :"<< d.count()<<" s"<<endl;
}


