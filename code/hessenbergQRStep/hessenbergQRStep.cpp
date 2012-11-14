
#include "../matrixHeaders.h"

//Overwrites H with H+ = RQ by algorthm 7.4.1
void hessenbergQRStep(arma::mat & H) {
    using namespace arma;

    int n = H.n_cols;

    //initialize n-1 givens matrices
    field<mat> G = field<mat>(n - 1, 1);
    mat Gk = zeros<mat>(2, 2);

    for (int k = 0; k < n - 1; k++) {
        givens(H(k, k), H(k + 1, k), Gk);
        G(k) = Gk;
        
        H(span(k, k + 1), span(k, n - 1)) = strans(Gk) * H(span(k, k + 1), span(k, n - 1));

    }

    for (int k = 0; k < n - 1; k++) {
        H(span(0, k + 1), span(k, k + 1)) = H(span(0, k + 1), span(k, k + 1)) * G(k);
    }
}
