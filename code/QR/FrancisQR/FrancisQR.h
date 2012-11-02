/* 
 * File:   FrancisQR.h
 * Author: jorgmeister
 *
 * Created on November 2, 2012, 8:35 PM
 */

#ifndef FRANCISQR_H
#define	FRANCISQR_H

class FrancisQR : public QR{
public:
    FrancisQR(arma::mat & A, double eps = 1E-6, int max_iter = 1000);
protected:

    arma::mat subA;
    int p, q;
    
    virtual void get_initial_condition(arma::mat & A);

    virtual void get_RQ(arma::mat & A);

};

#endif	/* FRANCISQR_H */

