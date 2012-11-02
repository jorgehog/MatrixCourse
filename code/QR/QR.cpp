/* 
 * File:   QR.cpp
 * Author: jorgmeister
 * 
 * Created on October 24, 2012, 2:01 PM
 */

#include "../matrixHeaders.h"

QR::QR(arma::mat & A, double eps, int max_iter) {
    this->A = A;
    this->eps = eps;
    this->max_iter = max_iter;
    this->n = A.n_cols;
    A_orig = A;
}

QR::QR() {

}

void QR::get_RQ(arma::mat & A) {
    arma::mat R, Q;

    qr(Q, R, A);

    A = R*Q;
}

void QR::deflate(arma::mat& A) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(A(j, i)) < eps) A(j, i) = 0;
        }
    }
}

void QR::iterate(bool dump) {
    using namespace arma;

    double cond;
    colvec subdiag;
    bool not_on_real_schur_form;


    iterations = 0;
    timer.tic();
    get_initial_condition(A);
    while (iterations < max_iter) {

        deflate(A);

        //calculate the condition
        subdiag = A.diag(-1);
        cond = dot(subdiag(span(1, n - 2)), subdiag(span(0, n - 3)));
//        if (dump) cout << "cond: " << cond << endl;

        //if cond == 0, we have a real schur form
        not_on_real_schur_form = (bool)(cond);
        if (!not_on_real_schur_form) {
            break;
        }

        get_RQ(A);
        iterations++;

    }

    get_eigvals_from_realschur(A);
    runtime = timer.toc();

    if (dump) {
        dump_results();
    }
}

void QR::dump_results() {
    using namespace std;
    using namespace arma;

    cx_vec eigval;
    cx_mat eigvec;

    if (iterations != max_iter) {
        cout << "Iterations completed after " << runtime << " seconds, with " << iterations << " iterations." << endl;
        cout << "Approximate eigenvalues with error " << eps << ":" << endl;
    } else {
        cout << "Iterations aborted after " << runtime << " seconds, with " << iterations << " iterations." << endl;
        cout << "Approximate eigenvalues:" << endl;
    }


    cout << eigvals << endl;

    cout << "\nEigenvalues by arma::eig_gen():" << endl;
    eig_gen(eigval, eigvec, A_orig);
    cout << eigval << endl;

}

void QR::get_eigvals_from_realschur(arma::mat& A) {
    using namespace arma;

    colvec subdiag = A.diag(-1);
    mat block;
    double re, im, det, re2;

    eigvals = zeros<mat > (n, 2);

    for (int i = 0; i < n - 1; i++) {

        //a block corner
        if (subdiag(i) != 0) {
            im = 0;
            re2 = 0;

            //block = [a b]
            //        [c d]
            block = A(span(i, i + 1), span(i, i + 1));

            //re = (a+d)/2
            re = 0.5 * (block(0, 0) + block(1, 1));

            det = block(0, 0) * block(1, 1) - block(0, 1) * block(1, 0);
         
            //check for complex eigenvalues
            if (re * re > det) {
                re2 = sqrt(re * re - det);
            } else {
                //im = sqrt(ad - bc - re^2)
                im = sqrt(det - re * re);
            }

            eigvals(i, 0) = re + re2;
            eigvals(i + 1, 0) = re - re2;

            eigvals(i, 1) = im;
            eigvals(i + 1, 1) = -im; //per def compl. conj. eigvals.


            //skip past the block
            i++;
        } else {
            eigvals(i, 0) = A(i, i);
        }
    }

    //If the last subdiag element is zero, we have an eigenvalue on the last diag el.
    if (A(n - 1, n - 2) == 0) {
        eigvals(n - 1, 0) = A(n - 1, n - 1);
    }


}