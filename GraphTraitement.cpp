//
// Created by laurent on 01/12/2019.
//

#include "GraphTraitement.h"

using namespace cv;
using namespace std;

void GraphTraitement::preTraitement(cv::VideoCapture captRef, cv::UMat &oldFrame) {
    int ex = static_cast<int>(captRef.get(cv::CAP_PROP_FOURCC));//on utilise le meme codecs c'est un peu nul
    cv::Size S = cv::Size((int) captRef.get(cv::CAP_PROP_FRAME_WIDTH),
                          (int) captRef.get(cv::CAP_PROP_FRAME_HEIGHT));
    outputVideo.open(file , ex, captRef.get(cv::CAP_PROP_FPS),S, true);
    indexFrame = 0;
    if (display) namedWindow("graph", WINDOW_AUTOSIZE);
}

void GraphTraitement::mainTraitement(cv::UMat &frame) {
// Eventuelement la gestion des fenetres
    if(indexFrame>plus){
        draw_graph( indexFrame-plus);
    }

    R_tab.push_back(*r);
    frameBuffer.push_back(frame);
    indexFrame++;
    // std::cout << endl << "Frame number :" << indexFrame << std::endl;
}

void GraphTraitement::postTraitement() {
    for(int i = plus-1; i>=0 ; i--){
        draw_graph( indexFrame-i);
    }
    outputVideo.release();
}

void GraphTraitement::draw_graph(int index) {
    //Code historique testé et aprouvé
    const UMat image = frameBuffer.front();
    int l = image.cols;
    int h = image.rows;
    //Axe Oy vertical
    cv::line(image,
             cv::Point(l / 10, h / 10),
             cv::Point(l / 10, 9 * h / 10),
             Scalar(10, 10, 10),
             2, 2, 0);
    cv::line(image,
             cv::Point(l / 10, h / 10),
             cv::Point(l / 10 - l / 100, h / 10 + h / 100),
             Scalar(10, 10, 10),
             2, 2, 0);
    cv::line(image,
             cv::Point(l / 10, h / 10),
             cv::Point(l / 10 + l / 100, h / 10 + h / 100),
             Scalar(10, 10, 10),
             2, 2, 0);

    //Axe Ox horizontal
    cv::line(image,
             cv::Point(l / 10, 9 * h / 10),
             cv::Point(9 * l / 10, 9 * h / 10),
             Scalar(10, 10, 10),
             2, 2, 0);
    cv::line(image,
             cv::Point(9 * l / 10, 9 * h / 10),
             cv::Point(9 * l / 10 - l / 100, 9 * h / 10 - h / 100),
             Scalar(10, 10, 10),
             2, 2, 0);
    cv::line(image,
             cv::Point(9 * l / 10, 9 * h / 10),
             cv::Point(9 * l / 10 - l / 100, 9 * h / 10 + h / 100),
             Scalar(10, 10, 10),
             2, 2, 0);

    //Tick horizontal
    for (int i = 0; i < 50; i += 10) {

        int x = l / 10 + i * (l * 80. / 5000.);

        int y = 9 * h / 10;
        cv::line(image,
                 cv::Point(x, y),
                 cv::Point(x, y + 4 * h / 100),
                 Scalar(10, 10, 10),
                 2, 2, 0);
    }
    int x = l / 10 + 40 * (l * 8. / 500.);
    cv::line(image,
             cv::Point(x, 9 * h / 10),
             cv::Point(x, h / 10),
             Scalar(10, 10, 255),
             2, 2, 0);
    int y = 9 * h / 10 - 0.7 * (h * 8 / 10.);
    cv::line(image,
             cv::Point(l / 10, y),
             cv::Point(9 * l / 10, y),
             Scalar(10, 255, 10),
             2, 2, 0);

    int x_last = l / 10;
    int y_last = 9 * h / 10;
    //cout<<"Boucle  : "<<R_tab.size() <<endl;
    //cout<<"Index : "<< index<< " deb : "<<max(index-minus, 0)<<", fin : "<< min(index+plus, (int)R_tab.size())<<endl;
    for (int i = max(index - minus, 0); i < (min(index + plus, (int) R_tab.size())); i++) {
        x = l / 10 + (i - index + minus) * (l * 8. / 500.);
        y = 9 * h / 10 - R_tab[i] * (h * 8 / 10.);

        cv::line(image,
                 cv::Point(x_last, y_last),
                 cv::Point(x, y),
                 Scalar(255, 255, 10),
                 2, 2, 0);
        x_last = x;
        y_last = y;
    }

    string frame = to_string(index) + " frame Nb";
    cv::putText(image,
                frame,
                cv::Point(6 * l / 10, h / 10),
                FONT_HERSHEY_SIMPLEX,
                1,
                Scalar(80, 180, 180));


    if (display) {
        imshow("graph", image);
        waitKey(1);
    }
    outputVideo.write(image.getMat(ACCESS_READ));
    frameBuffer.pop_front();

}