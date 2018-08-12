#include "autoadaptation.h"

AdaptationParameters::AdaptationParameters()
{
}
ParamsToAdapt_t AdaptationParameters::generateRandomParams(){
    ParamsToAdapt_t tmp_params;
    tmp_params.treshold_lvl_ = rand() % 255;
    tmp_params.treshold_type_ = rand() % 5;
    tmp_params.alpha_ = ((float)((rand() % 19)+10)/10);
    tmp_params.beta_ = rand() % 100;

    return tmp_params;
}


bool AdaptationParameters::operator>
(ParamsToAdapt_t & param)
{
    bool retVal = false;

    for(auto local_param : params_to_adapt[].confidences_v){
        if (local_param )
    }

}
