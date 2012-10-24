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

    unsigned long seed = time(NULL);
    srand(seed);
    argc = 2;
    if (argc == 1) {
        mat A;
        //    A<< 1 << 3 <<-3 << endr
        //     <<-3 << 7 <<-3 << endr
        //     <<-6 << 6 <<-2 << endr;
        A = symmatl(randu<mat > (5, 5));


        QR* qr = new QR(A);
        qr->iterate();

        cout << "-----------------------" << endl;

        QR* hessQR = new HessenbergQR(A);
        hessQR->iterate();

        cout << "-----------------------" << endl;

        QR* shiftQR = new shiftedQR(A);
        shiftQR->iterate();
    } else {
        QR* qr;
        QR* hessQR;
        QR* shiftQR;
        mat A;
        for (int n = 100; n <= 500; n += 50) {
            cout << "n=" << n << endl;
            srand(-time(NULL) + n);
            A = symmatl(randu<mat > (n, n))+ eye<mat>(n,n)*1.1;

            qr = new QR(A);
            qr->iterate(false);
            cout << 0 << ":QR:" << qr->get_runtime() << ":" << qr->get_iters()<<endl;

            hessQR = new HessenbergQR(A);
            hessQR->iterate(false);
            cout << 1 << ":HESS:" << hessQR->get_runtime()<< ":" << hessQR->get_iters() << endl;

            

            shiftQR = new shiftedQR(A);
            shiftQR->iterate(false);
            cout << 2 << ":SHIFT:" << shiftQR->get_runtime()<< ":" << shiftQR->get_iters() << endl;
        }
    }

    return 0;
}