
#include "../matrixHeaders.h"

void givens(double a, double b, arma::mat & G) {
    double tau, c, s;

    if (b == 0) {
        c = 1;
        s = 0;
    } else {

        if (b * b > a * a) {
            tau = -a / b;
            s = 1 / sqrt(1 + tau * tau);
            c = s*tau;
        } else {
            tau = -b / a;
            c = 1 / sqrt(1 + tau * tau);
            s = c*tau;
        }
    }

    G(0, 0) = c;
    G(1, 1) = c;
    G(0, 1) = s;
    G(1, 0) = -s;

}