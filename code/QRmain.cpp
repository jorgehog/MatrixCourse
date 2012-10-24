/* 
 * File:   main.cpp
 * Author: jorgmeister
 *
 * Created on October 19, 2012, 1:48 PM
 */

#include "matrixHeaders.h"

/*
 * 
 */

int main(int argc, char** argv) {
    using namespace arma;
    using namespace std;

    mat A;
//    A<< 1 << 3 <<-3 << endr
//     <<-3 << 7 <<-3 << endr
//     <<-6 << 6 <<-2 << endr;
    A = symmatu(randu<mat>(100,100));

    
    QR* qr = new QR(A);
    qr->iterate();
    
    cout << "-----------------------" << endl;
    
    QR* hessQR = new HessenbergQR(A);
    hessQR->iterate();
    
    cout << "-----------------------" << endl;
    
    QR* shiftQR = new shiftedQR(A);
    shiftQR->iterate();
    
    return 0;
}