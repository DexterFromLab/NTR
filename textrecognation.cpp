#include "textrecognation.h"

using namespace std;
using namespace cv;
using namespace cv::text;

TextRecognation::TextRecognation(vector <Mat> images, vector <Rect> rectangles):images_(images),rectangles_(rectangles)
{

};

void TextRecognation::recognateNumber(){

    string vocabulary = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // must have the same order as the classifier output classes
    Ptr<OCRHMMDecoder::ClassifierCallback> ocr = loadOCRHMMClassifierCNN("../NTR/classificators/OCRBeamSearch_CNN_model_data.xml.gz");

    vector<int> out_classes;
    vector<double> out_confidences;

    recognation_results.recognised_signs_.clear();
    recognation_results.confidences_.clear();

    for(auto image : images_){
        ocr->eval(image, out_classes, out_confidences);

        //qDebug() << "OCR output = \"" << vocabulary[out_classes[0]] << "\" with confidence " <<out_confidences[0];
        recognation_results.recognised_signs_.push_back(vocabulary[out_classes[0]]);
        recognation_results.confidences_.push_back(out_confidences[0]);
    }

}
