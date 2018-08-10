#ifndef RECTANGLEDETECTOR_H
#define RECTANGLEDETECTOR_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/types.hpp"
#include <opencv2/opencv.hpp>
#include <vector>


class RectangleDetector
{
public:
    RectangleDetector();
    std::vector <cv::Mat> pictures_to_recognation;
    std::vector<cv::Rect> groups_boxes;

    void displayAllSherds(void);
    void clearAllShreads(void);
    void changeAllShreadsToGray(void);
    void changeAllShreadsTreshold(int lvl);
protected:
    const std::string window_name = "Catched_rectangle";
    virtual std::vector<cv::Rect> retBoxes(){
        return groups_boxes;
    }
};

class ManualDetect : public RectangleDetector{
public:
    void detectBoxes(const cv::Mat & image);
    void mouseCallback(int event, int x, int y);
    int mouseClickedOnce = 0;
    static void mouseCallback(int event, int x, int y, int, void* userdata);

private:
    const std::string window_name = "Catch_rectangle";
    cv::Point_<int> first_click_;
    cv::Point_<int> second_click_;
    cv::Point_<int> last_move_;
    cv::Rect_ <int> rect_to_red_;
    cv::Rect_ <int> rect_marker_;
};
#endif // RECTANGLEDETECTOR_H
