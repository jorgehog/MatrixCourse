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

void QR::get_RQ() {
    arma::mat R, Q;

    qr(Q, R, A);

    A = R*Q;
}

void QR::iterate(bool dump) {

    double cond = eps + 1;
    double cond_prev = 0;


    iterations = 0;

    timer.tic();
    get_initial_condition(A);

    while ((fabs(cond - cond_prev) > eps) && (iterations < max_iter)) {
        get_RQ();


        cond_prev = cond;
        cond = arma::prod(A.diag());

        if (dump) {
            std::cout << "cond: " << cond << std::endl;
        }

        iterations++;
    }

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


    cout << A.diag() << endl;

    cout << "\nEigenvalues by arma::eig_gen():" << endl;
    eig_gen(eigval, eigvec, A_orig);
    cout << real(eigval) << endl;

}

