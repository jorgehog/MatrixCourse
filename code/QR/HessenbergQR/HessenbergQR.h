/* 
 * File:   HessenbergQR.h
 * Author: jorgmeister
 *
 * Created on October 24, 2012, 2:01 PM
 */

#ifndef HESSENBERGQR_H
#define	HESSENBERGQR_H

class HessenbergQR : public QR {
public:
    HessenbergQR(arma::mat & A, double eps = 1E-6, int max_iter = 1000);

//    friend class shiftedQR;
    
protected:

    virtual void get_initial_condition(arma::mat & A);

    virtual void get_RQ(arma::mat & A);
};

#endif	/* HESSENBERGQR_H */

