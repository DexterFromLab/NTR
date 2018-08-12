#ifndef AUTOADAPTATION_H
#define AUTOADAPTATION_H

#include <vector>
#include <QtDebug>
#include <QCoreApplication>
#include "textrecognation.h"
#include "rectangledetector.h"

using namespace std;

typedef  struct {
     int treshold_lvl_;
     int treshold_type_;
     float alpha_;
     int beta_;
     vector <double> confidences_v;
 }ParamsToAdapt_t;

class AdaptationParameters
{
public:
    AdaptationParameters();
    ParamsToAdapt_t generateRandomParams();
    //True if all first_param.confidences > second_param.confidences
    bool operator>(ParamsToAdapt_t & param);
private:
    vector<ParamsToAdapt_t> params_to_adapt;


private:

};

class AutoAdaptation
{
public:
    AutoAdaptation();
private:
   int size_of_population = 100;
   int mutation_rate = 0.1;
};

#endif // AUTOADAPTATION_H
