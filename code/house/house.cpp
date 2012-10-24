
#include "../matrixHeaders.h"

void house(arma::mat & ImBvvT, arma::colvec & x) {
    using namespace arma;
    
    double sigma, mu, beta;

    int n = x.n_rows;

    colvec xspan = x(span(1, n - 1));
    sigma = dot(xspan, xspan);

    colvec v = zeros<colvec > (n);
    v(span(1, n - 1)) = xspan;

    //zero if sigma is zero
    if (sigma == 0) {
        beta = 0;
    } else {
        mu = sqrt(x(0) * x(0) + sigma);

        if (x(0) <= 0) {
            v(0) = x(0) - mu;
        } else {
            v(0) = -sigma / (x(0) + mu);
        }

        beta = 2 / (sigma / (v(0) * v(0)) + 1);
        v /= v(0);
    }
    
    ImBvvT = eye<mat > (n, n) - beta * v * strans(v);
}
