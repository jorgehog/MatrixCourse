/* 
 * File:   matrixHeaders.h
 * Author: Computational Physics UiO 2012
 *
 * Created on October 19, 2012, 1:51 PM
 */

#ifndef MATRIXHEADERS_H
#define	MATRIXHEADERS_H

#include <armadillo>
#include <iostream>
#include <math.h>

using namespace arma;

/*
 
 CHAPTER 7.4
 
 */

//Calulates a HouseHolder vector by algorthm 5.1.1
void house(double & beta, colvec & v, colvec & x);

//Calculates the givens rotation matrix G given a and b by algorithm 5.1.3
void givens(double a, double b, mat & G);

//Overwrites A with H= U0^T A U_0 where H is upper Hessenberg. Algorthm 7.4.2
void householderRedHessenberg(mat & A);

//Overwrites H with H+ = RQ by algorthm 7.4.1
void hessenbergQRStep(mat & H);


#endif	/* MATRIXHEADERS_H */

