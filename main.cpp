#include <QCoreApplication>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/types.hpp"

#include "rectangledetector.h"
#include "textrecognation.h"
using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Mat image = imread("/home/bartek/Repositories/NTR/counter0.jpg");

    ManualDetect detector;

    detector.detectBoxes(image);
    detector.changeAllShreadsToGray();
    //detector.changeAllShreadsTreshold(40);

    TextRecognation recognation(detector.pictures_to_recognation, detector.groups_boxes);
    detector.filtersAutoadaptation("007",recognation);
    recognation.recognateNumber();

    return a.exec();
}

