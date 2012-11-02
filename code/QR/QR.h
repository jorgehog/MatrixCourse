/* 
 * File:   QR.h
 * Author: jorgmeister
 *
 * Created on October 24, 2012, 2:01 PM
 */

#ifndef QR_H
#define	QR_H

class QR {
protected:
    int n;
    
    int iterations;
    double runtime;

    int max_iter;
    double eps;

    arma::mat A;
    arma::mat A_orig;
    arma::wall_clock timer;
    arma::mat eigvals;

    void dump_results();
    
    void deflate(arma::mat & A);
    
    virtual void get_initial_condition(arma::mat & A) {

    }

    void get_eigvals_from_realschur(arma::mat & A);
    
    virtual void get_RQ(arma::mat & A);

public:
    QR(arma::mat & A, double eps = 1E-6, int max_iter = 1000);
    QR();

    void iterate(bool dump = true);
    double get_runtime() {
        return runtime;
    }
    
    int get_iters() {
        return iterations;
    }
};

#endif	/* QR_H */

