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

    void dump_results();

    virtual void get_initial_condition(arma::mat & A) {

    }

    virtual void get_RQ();

public:
    QR(arma::mat & A, double eps = 1E-6, int max_iter = 1000);

    void iterate();

};

#endif	/* QR_H */

