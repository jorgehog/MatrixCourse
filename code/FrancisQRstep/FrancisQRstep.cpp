
#include "../matrixHeaders.h"

void FrancisQRstep(arma::mat & H) {
    using namespace arma;

    int q, r;

    arma::mat ImBvvT;
    arma::colvec xyz = zeros<colvec > (3);

    int n = H.n_cols - 1;
    int m = n - 1;

    double s = H(m, m) + H(n, n);
    double t = H(m, m) * H(n, n) - H(m, n) * H(n, m);

    xyz(0) = H(0, 0) * H(0, 0) + H(0, 1) * H(1, 0) - s * H(0, 0) + t;
    xyz(1) = H(1, 0)*(H(0, 0) + H(1, 1) - s);
    xyz(2) = H(1, 0) * H(2, 1);

    for (int k = -1; k < n - 2; k++) {

        house(ImBvvT, xyz);
        
        //q = max(0, k);
        q = k * (int) (k > 0);

        H(span(k + 1, k + 3), span(q, n)) = ImBvvT * H(span(k + 1, k + 3), span(q, n));

        //r = min(k+4, n)
        r = (k + 4 - n)*(int) (k + 4 < n) + n;
        
        H(span(0, r), span(k+1, k+3)) = H(span(0, r), span(k+1, k+3))*ImBvvT;
        
        xyz(0) = H(k+2, k+1);
        xyz(1) = H(k+3, k+1);
        
        if (k < n-3){
            xyz(2) = H(k+4, k+1);
        }
    }
    
    colvec xy = xyz.rows(0, 1);
    house(ImBvvT, xy);
    H(span(n-1, n), span(n-2, n)) = ImBvvT*H(span(n-1, n), span(n-2, n));
    H(span(0,n), span(n-1, n)) = H(span(0,n), span(n-1, n))*ImBvvT;

}
