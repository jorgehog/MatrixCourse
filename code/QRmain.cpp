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
//    argc = 2;

    if (argc == 4) {
        int N = atoi(argv[1]);
        if (N < 4){
            cout << "Solver only works for N>3. Aborting." << endl;
            exit(1);
        }
        double eps = atof(argv[2]);
        double Nmax = atoi(argv[3]);
//        int N = 5;
        mat A;
        //        A << 1 << 3 << -3 << endr
        //                << -3 << 7 << -3 << endr
        //                << -6 << 6 << -2 << endr;
        A = randu<mat > (N, N);

        cout << "-----------QR----------" << endl;

        QR* qr = new QR(A, eps, Nmax);
        qr->iterate();

        cout << "-------Hessenberg------" << endl;

        QR* hessQR = new HessenbergQR(A, eps, Nmax);
        hessQR->iterate();

        cout << "-------singleShift------" << endl;

        QR* shiftQR = new shiftedQR(A, eps, Nmax);
        shiftQR->iterate();

        cout << "---------Francis--------" << endl;

        QR* francisQR = new FrancisQR(A, eps, Nmax);
        francisQR->iterate();

    } else {
        QR* qr;
        QR* hessQR;
        QR* shiftQR;
        mat A;
        for (int n = 100; n <= 500; n += 50) {
            cout << "n=" << n << endl;
            srand(-time(NULL) + n);
            A = symmatl(randu<mat > (n, n)) + eye<mat > (n, n)*1.1;

            qr = new QR(A);
            qr->iterate(false);
            cout << 0 << ":QR:" << qr->get_runtime() << ":" << qr->get_iters() << endl;

            hessQR = new HessenbergQR(A);
            hessQR->iterate(false);
            cout << 1 << ":HESS:" << hessQR->get_runtime() << ":" << hessQR->get_iters() << endl;



            shiftQR = new shiftedQR(A);
            shiftQR->iterate(false);
            cout << 2 << ":SHIFT:" << shiftQR->get_runtime() << ":" << shiftQR->get_iters() << endl;
        }
    }

    return 0;
}