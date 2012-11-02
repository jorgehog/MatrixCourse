/* 
 * File:   shiftedQR.h
 * Author: jorgmeister
 *
 * Created on October 24, 2012, 2:53 PM
 */

#ifndef SHIFTEDQR_H
#define	SHIFTEDQR_H

class shiftedQR : public QR {
public:
    shiftedQR(arma::mat & A, double eps = 1E-6, int max_iter = 1000);

private:
    
    arma::mat I;
    arma::mat muI;
    
    virtual void get_initial_condition(arma::mat & A);

    virtual void get_RQ(arma::mat & A);
};

#endif	/* SHIFTEDQR_H */

