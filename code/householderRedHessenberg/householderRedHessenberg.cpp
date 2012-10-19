
#include "../matrixHeaders.h"

void householderRedHessenberg(arma::mat & A) {
    using namespace arma;


    double beta;
    colvec v, x;
    mat ImBvvT;

    int n = A.n_cols;

    for (int k = 0; k < n - 2; k++) {
        x = A(span(k + 1, n - 1), k);
        house(beta, v, x);
        A(span(k + 1, n - 1), k) = x;

        ImBvvT = eye<mat > (n - k - 1, n - k - 1) - beta * v * strans(v);
        A(span(k + 1, n - 1), span(k, n - 1)) = ImBvvT * A(span(k + 1, n - 1), span(k, n - 1));
        A(span(), span(k + 1, n - 1)) = A(span(), span(k + 1, n - 1)) * ImBvvT;
    }
}
