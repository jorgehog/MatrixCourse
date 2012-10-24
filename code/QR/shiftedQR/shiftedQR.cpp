/* 
 * File:   shiftedQR.cpp
 * Author: jorgmeister
 * 
 * Created on October 24, 2012, 2:53 PM
 */

#include "../../matrixHeaders.h"
#include "shiftedQR.h"

shiftedQR::shiftedQR(arma::mat & A, double eps, int max_iter)
: QR(A, eps, max_iter) {
    
    I = arma::eye(n, n);

}

void shiftedQR::get_initial_condition(arma::mat& A) {
    householderRedHessenberg(A);
}

void shiftedQR::get_RQ() {

    //mu*I
    muI = A(n - 1, n - 1)*I;
    
    A = A - muI;
    hessenbergQRStep(A);
    A = A + muI;
    
}
