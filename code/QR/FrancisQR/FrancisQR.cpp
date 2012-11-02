/* 
 * File:   FrancisQR.cpp
 * Author: jorgmeister
 * 
 * Created on November 2, 2012, 8:35 PM
 */

#include "../../matrixHeaders.h"

FrancisQR::FrancisQR(arma::mat & A, double eps, int max_iter)
: QR(A, eps, max_iter) {

}

void FrancisQR::get_initial_condition(arma::mat& A) {
    householderRedHessenberg(A);
}

void FrancisQR::get_RQ(arma::mat & A) {
    using namespace arma;
    
    //Find p, q such that they pick out the largest unreduced hessenberg submatrix
    p = (int) ((A(1, 0) != 0)&(A(2, 1) == 0));
    q = (n - 1) - (int) ((A(n - 1, n - 2) != 0)&(A(n - 2, n - 3) == 0));

    while ((A(q, q - 1) == 0)) {
        q--;
    }

    while ((A(p + 1, p) == 0) && (p != q)) {
        p++;
    }

    //perform a Francis QR step on this submatrix (ineffective this way but..)
    subA = A(span(p, q), span(p, q));
    FrancisQRstep(subA);
    A(span(p, q), span(p, q)) = subA;
    
}

