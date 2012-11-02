/* 
 * File:   matrixHeaders.h
 * Author: Computational Physics UiO 2012
 *
 * Created on October 19, 2012, 1:51 PM
 */

#ifndef MATRIXHEADERS_H
#define	MATRIXHEADERS_H

//#define ARMA_NO_DEBUG

#include <armadillo>
#include <iostream>
#include <math.h>
#include <time.h>

/*
 
 CHAPTER 7.4
 
 */

//Calulates a HouseHolder vector v and returns I - beta*v*vT by algorthm 5.1.1
void house(arma::mat & ImBvvT, arma::colvec & x);

//Calculates the givens rotation matrix G given a and b by algorithm 5.1.3
void givens(double a, double b, arma::mat & G);

//Overwrites A with H= U0^T A U_0 where H is upper Hessenberg. Algorthm 7.4.2
void householderRedHessenberg(arma::mat & A);

//Overwrites H with H+ = RQ by algorthm 7.4.1
void hessenbergQRStep(arma::mat & H);

//Overwrites H with Z^T H Z by algorithm 7.5.1
void FrancisQRstep(arma::mat & H);

#include "QR/QR.h"
#include "QR/HessenbergQR/HessenbergQR.h"
#include "QR/shiftedQR/shiftedQR.h"
#include "QR/FrancisQR/FrancisQR.h"


#endif	/* MATRIXHEADERS_H */

