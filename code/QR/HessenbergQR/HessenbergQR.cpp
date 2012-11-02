/* 
 * File:   HessenbergQR.cpp
 * Author: jorgmeister
 * 
 * Created on October 24, 2012, 2:01 PM
 */

#include "../../matrixHeaders.h"

HessenbergQR::HessenbergQR(arma::mat& A, double eps, int max_iter)
: QR(A, eps, max_iter) {

}

void HessenbergQR::get_RQ(arma::mat & A){
    hessenbergQRStep(A);
}

void HessenbergQR::get_initial_condition(arma::mat& A){
    householderRedHessenberg(A);
}