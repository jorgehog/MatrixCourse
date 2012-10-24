
#include "../matrixHeaders.h"

void householderRedHessenberg(arma::mat & A) {
    using namespace arma;

    colvec x;
    mat ImBvvT;

    int n = A.n_cols;

    for (int k = 0; k < n - 2; k++) {
        x = A(span(k + 1, n - 1), k);
        house(ImBvvT, x);
        A(span(k + 1, n - 1), k) = x;

        A(span(k + 1, n - 1), span(k, n - 1)) = ImBvvT * A(span(k + 1, n - 1), span(k, n - 1));
        A(span(), span(k + 1, n - 1)) = A(span(), span(k + 1, n - 1)) * ImBvvT;
    }
}
