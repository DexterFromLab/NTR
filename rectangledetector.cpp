#include "rectangledetector.h"
#include <string>
#include <iostream>
#include <cstdlib>

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
    waitKey(10);
}
void RectangleDetector::changeAllShreadsToGray(){

   for(unsigned int i = 0 ; i < pictures_to_recognation.size() ; i++){

        cv::cvtColor(pictures_to_recognation[i], pictures_to_recognation[i], cv::COLOR_RGB2GRAY);

    }

}
/*
   Function: changeAllShreadsFilters
   Applies threshold, brightness and contrast filters to selected pictures
   Parameters:
      treshold_lvl  - 0 : 255
      treshold_type - 0: Binary
                      1: Binary Inverted
                      2: Threshold Truncated
                      3: Threshold to Zero
                      4: Threshold to Zero Inverted
      alpha         - Enter the alpha value [1.0-3.0]: 2.2
      beta          - Enter the beta value [0-100]: 50
   Returns:
      void

*/
void RectangleDetector::changeAllShreadsFilters(int treshold_lvl,int treshold_type, float alpha, int beta){

    for(unsigned int i = 0 ; i < pictures_to_recognation.size() ; i++){

         threshold( pictures_to_recognation[i], pictures_to_recognation[i], treshold_lvl, 255,treshold_type);
         pictures_to_recognation[i].convertTo(pictures_to_recognation[i],-1,alpha,beta);
     }

}

void RectangleDetector::filtersAutoadaptation(const char * realSigns, TextRecognation &detector){
    Mat originPicturesCopy[pictures_to_recognation.size()];

    for(int i = 0 ; i < pictures_to_recognation.size() ; i++){
        pictures_to_recognation[i].copyTo(originPicturesCopy[i]);
    }

    int found_solution_flag = 0;

    vector <int> treshold_lvl_v;
    vector <int> treshold_type_v;
    vector <float> alpha_v;
    vector <int> beta_v;
    vector <double> confidences[pictures_to_recognation.size()];

    const int size_of_population = 100;
    const int mutation_rate = 0.1;
    //Generate random population
    for(unsigned int i = 0 ; i < size_of_population ; i++){
        treshold_lvl_v.push_back(rand() % 255);
        treshold_type_v.push_back(rand() % 5);
        alpha_v.push_back((double)((rand() % 19)+10)/10);
        beta_v.push_back(rand() % 100);
    }

    while(1){
        //Check population codition
        for(unsigned int i = 0 ; i < size_of_population ; i++){
            changeAllShreadsFilters(treshold_lvl_v[i],treshold_type_v[i], alpha_v[i], beta_v[i]);
            qDebug() << treshold_lvl_v[i] << treshold_type_v[i] << alpha_v[i] << beta_v[i] << endl;
            detector.recognateNumber();

            for(unsigned int y = 0 ; y < detector.recognation_results.confidences_.size() ; y++){
                confidences[y].push_back(detector.recognation_results.confidences_[y]);
            }

            displayAllSherds();

            for(int y = 0 ; y < pictures_to_recognation.size() ; y++){
                originPicturesCopy[y].copyTo(pictures_to_recognation[y]);
            }
        }
        //Sort population
        qDebug()<<"===============";
        for(unsigned int i = 0 ; i < size_of_population ; i++){
            qDebug()<<treshold_lvl_v[i];
        }
       int change = 0;
       for(unsigned int i = 0 ; i < size_of_population ; i++){
           int better_flag = 0;
           for(unsigned int y = 0 ; y < detector.recognation_results.confidences_.size()-1 ; y++){
               if(confidences[i][y] < confidences[i+1][y]){
                   better_flag++;
               }
           }
           if(better_flag == detector.recognation_results.confidences_.size() - 1){
               qDebug()<<"Found better solution!";
               int treshold_lvl_tmp = treshold_lvl_v[i];
               int treshold_type_tmp = treshold_type_v[i];
               float alpha_tmp = alpha_v[i];
               int beta_tmp = beta_v[i];
               double confidences_tmp[pictures_to_recognation.size()];

               for(unsigned int y = 0 ; y < detector.recognation_results.confidences_.size() ; y++){
                   confidences_tmp[y] = confidences[i][y];
               }

               treshold_lvl_v[i] = treshold_lvl_v[i+1];
               treshold_type_v[i] = treshold_type_v[i+1];
               alpha_v[i] = alpha_v[i+1];
               beta_v[i] = beta_v[i+1];
               for(unsigned int y = 0 ; y < detector.recognation_results.confidences_.size() ; y++){
                   confidences[i][y] = confidences[i+1][y];
               }

               treshold_lvl_v[i+1] = treshold_lvl_tmp;
               treshold_type_v[i+1] = treshold_type_tmp;
               alpha_v[i+1] = alpha_tmp;
               beta_v[i+1] = beta_tmp;
               for(unsigned int y = 0 ; y < detector.recognation_results.confidences_.size() ; y++){
                   confidences[i+1][y] = confidences_tmp[y];
               }
           }
           if(change == 0) break;
       }
       qDebug()<<"===============";
       for(unsigned int i = 0 ; i < size_of_population ; i++){
           qDebug()<<treshold_lvl_v[i];
       }
    }
}

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
