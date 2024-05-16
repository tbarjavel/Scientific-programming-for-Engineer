#include "series.hh"

int computeSeries(int n) {
    int S = 0;
    for (int k = 1; k < n + 1; ++k) {
        S += k;
    }
    return S;
}
