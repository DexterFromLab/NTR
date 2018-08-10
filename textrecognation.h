#ifndef TEXTRECOGNATION_H
#define TEXTRECOGNATION_H

#include <vector>
#include <string>
#include "opencv2/core/types.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/text.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <QCoreApplication>
#include <QtDebug>

class TextRecognation
{
public:
    TextRecognation(std::vector <cv::Mat> images, std::vector <cv::Rect> rectangles);
    void recognateNumber();
protected:
    std::vector <cv::Mat> images_;
    std::vector <cv::Rect> rectangles_;
    std::vector <std::string> texts_;
};

#endif // TEXTRECOGNATION_H
