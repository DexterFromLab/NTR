#include "rectangledetector.h"
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

RectangleDetector::RectangleDetector()
{

}
void RectangleDetector::displayAllSherds(void){
    int i = 0;
    for(auto shred : pictures_to_recognation){
        imshow(window_name + to_string(i), shred);
        i++;
    }
    namedWindow(window_name,WINDOW_NORMAL);
}
void on_push(int state, void*) {}

void ManualDetect::detectBoxes(const Mat & image){
    char pessedKey = 0;

    while(pessedKey != 27){
        Mat imageCopy;
        image.copyTo(imageCopy);
        namedWindow(window_name,WINDOW_NORMAL);
        putText(imageCopy, "First x: " + to_string(first_click_.x) +" first y: " + to_string(first_click_.y), Point2f(25,75), FONT_HERSHEY_SIMPLEX, 2,  Scalar(0,255,255,255),6);
        putText(imageCopy, "Second x: " + to_string(second_click_.x) +" second y: " + to_string(second_click_.y), Point2f(25,150), FONT_HERSHEY_SIMPLEX, 2,  Scalar(0,255,255,255),6);
        putText(imageCopy, "Pos x: " + to_string(last_move_.x) +" pos y: " + to_string(last_move_.y), Point2f(25,225), FONT_HERSHEY_SIMPLEX, 2,  Scalar(0,255,255,255),6);

        if((second_click_.x != 0 && second_click_.y != 0)){
            rectangle(imageCopy, rect_to_red_, Scalar(0,255,255,255), 6);
        }

        if(mouseClickedOnce){
            rectangle(imageCopy, rect_marker_, Scalar(0,255,255,255), 6);
        }

        for(auto recangle : groups_boxes){
            rectangle(imageCopy, recangle, Scalar(0,0,255,0), 6);
        }

        imshow(window_name,imageCopy);
        resizeWindow(window_name,800,600);
        setMouseCallback(window_name, mouseCallback, this);

        if(pessedKey == 'c' && rect_to_red_.size().height > 0 && rect_to_red_.size().width > 0){
            groups_boxes.push_back(rect_to_red_);
        }

        if(pessedKey == 13){

            for(auto rectangle : groups_boxes){
                pictures_to_recognation.push_back(image(rectangle));
            }
            destroyWindow(window_name);
            break;
        }

        pessedKey = waitKey(50);
    }
    return;
}


void ManualDetect::mouseCallback(int  event, int  x, int  y, int, void *userdata)
{
    ManualDetect* manualdetect = reinterpret_cast<ManualDetect*>(userdata);

    if (event == EVENT_LBUTTONDOWN) {

        if(manualdetect->mouseClickedOnce == 0){
            manualdetect->mouseClickedOnce = 1;
            manualdetect->first_click_ = Point2i(x,y);
        }else{
            manualdetect->mouseClickedOnce = 0;
            manualdetect->second_click_ = Point2i(x,y);
            manualdetect->rect_to_red_ = Rect_<int>(manualdetect->first_click_ , manualdetect->second_click_);
        }

    }

    if (event == EVENT_MOUSEMOVE){
        manualdetect->last_move_ =  Point2i(x,y);
        manualdetect->rect_marker_ = Rect_<int>(manualdetect->first_click_ , Point2i(x,y));
    }
}
