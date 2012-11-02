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
    argc = 1;


    /////
    //    mat A;
    //    mat subA;
    //    int n = 6;
    //    A = randu<mat > (n, n);
    //
    //    cx_vec eigval;
    //    cx_mat eigvec;
    //
    //    eig_gen(eigval, eigvec, A);
    //    cout << eigval << endl;
    //
    //    double tol = 1E-6;
    //    householderRedHessenberg(A);
    //
    //    int p, q, l;
    //
    //    bool not_on_real_schur_form;
    //    colvec subdiag;
    //            
    //    while (true) {
    //        p = (int) ((A(1, 0) != 0)&(A(2, 1) == 0));
    //        q = (n - 1) - (int) ((A(n - 1, n - 2) != 0)&(A(n - 2, n - 3) == 0));
    ////        l = n - 1;
    //
    //        //deflation;
    //        for (int i = 0; i < n; i++) {
    //            for (int j = i + 1; j < n; j++) {
    //                if (fabs(A(j, i)) < tol) A(j, i) = 0;
    //            }
    //        }
    //
    //
    //        while ((A(q, q - 1) == 0)) {
    //            q--;
    //        }
    //
    //        while ((A(p + 1, p) == 0) && (p != q)) {
    //            p++;
    //        }
    //
    //        //        while (l > 2) {
    //        //            if (A(l - 1, l - 2)*(A(l - 2, l - 3)) != 0) {
    //        //                stop = false;
    //        //            }
    //        //            l--;
    //        //        }
    //
    //        subdiag = A.diag(-1);
    //        not_on_real_schur_form = (bool)(dot(subdiag(span(1, n - 2)), subdiag(span(0, n - 3))));
    //        if (!not_on_real_schur_form) {
    //            break;
    //        }
    //
    //
    //        subA = A(span(p, q), span(p, q));
    //        FrancisQRstep(subA);
    //        A(span(p, q), span(p, q)) = subA;
    //
    //
    //
    //    }
    //
    //    cout << A << endl;
    /////

    if (argc == 1) {
        mat A;
        //        A << 1 << 3 << -3 << endr
        //                << -3 << 7 << -3 << endr
        //                << -6 << 6 << -2 << endr;
        A = randu<mat > (5, 5);

        cout << "-----------QR----------" << endl;

        QR* qr = new QR(A);
        qr->iterate();

        cout << "-------Hessenberg------" << endl;

        QR* hessQR = new HessenbergQR(A);
        hessQR->iterate();

        cout << "-------singleShift------" << endl;

        QR* shiftQR = new shiftedQR(A);
        shiftQR->iterate();

        cout << "---------Francis--------" << endl;

        QR* francisQR = new FrancisQR(A);
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