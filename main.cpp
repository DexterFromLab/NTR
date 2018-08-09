#include <QCoreApplication>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "rectangledetector.h"
#include "opencv2/core/types.hpp"
using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Mat image = imread("/home/bartosz/Dokumenty/Repositories/text_detector/NTR/counter0.jpg");

    ManualDetect detector;

    detector.detectBoxes(image);

    cv::Point_<int> first_click_ (0,0);

    return a.exec();
}
