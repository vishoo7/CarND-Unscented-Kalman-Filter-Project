#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
    VectorXd rmse(4);
    rmse << 0,0,0,0;

    int n = estimations.size();
    // check the validity of the following inputs:
    //  * the estimation vector size should not be zero
    if(n == 0){
        cout << "Estimation vector size should not be zero";
        return rmse;
    }
    //  * the estimation vector size should equal ground truth vector size
    if(n != ground_truth.size()){
        cout << "Estimation vector size should be the same as ground truth vector size";
        return rmse;
    }

    VectorXd residual(4);
    //accumulate squared residuals
    for(unsigned int i=0; i < n; ++i){

        residual = estimations[i] - ground_truth[i];

        //coefficient-wise multiplication
        residual = residual.array()*residual.array();
        rmse += residual;
    }

    //calculate the mean
    rmse = rmse/n;

    //calculate the squared root
    rmse = rmse.array().sqrt();

    //return the result
    return rmse;

}