//
// Created by laurent on 03/12/2019.
//

#include "cutTraitement.h"
#include "check_dir.h"

using namespace std;
using namespace cv;
#define CUT_VALUE 0.7

using namespace boost::filesystem;

void CutTraitement::preTraitement(VideoCapture *captRef, cv::UMat &oldFrame) {
    ex = static_cast<int>(captRef->get(cv::CAP_PROP_FOURCC));//on utilise le meme codecs c'est un peu nul
    S = cv::Size((int) captRef->get(cv::CAP_PROP_FRAME_WIDTH),
                 (int) captRef->get(cv::CAP_PROP_FRAME_HEIGHT));
    fps = captRef->get(cv::CAP_PROP_FPS);

    directory = path(file);
    //TODO gérer l'exeption mieux

    if (check_dir(directory) == -1) throw (string) "Probleme pour le repertoire de sortie";

    file_index = 0;
    string out_name = make_name(directory, file_index, ".avi");

    outputVideo.open(out_name, ex, fps, S, true);

}

void CutTraitement::mainTraitement(cv::UMat &frame) {
    if (*r > CUT_VALUE) {
        file_index++;
        outputVideo.release();
        string out_name = make_name(directory, file_index, ".avi");
        outputVideo.open(out_name, ex, fps, S, true);

    }
    outputVideo << frame.getMat(ACCESS_READ);
}

void CutTraitement::postTraitement() {
    outputVideo.release();
}
