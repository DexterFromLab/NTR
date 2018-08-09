#include <QCoreApplication>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "rectangledetector.h"
#include "opencv2/core/types.hpp"
using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Mat image = imread("/home/bartek/Pictures/gazety/Wspolczesna20092016.jpg");

    ManualDetect detector;

    detector.detectBoxes(image);
    detector.displayAllSherds();


    return a.exec();
}

