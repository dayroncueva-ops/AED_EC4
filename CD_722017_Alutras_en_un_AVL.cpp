#include <iostream>
#include <cmath>
using namespace::std;

int altura_minima (long long N) {
    int altura = 0;
    while (N>=2) {
        N = N /2;
        altura++;
    }
    return altura;
}

long long altura_maxima (long long N) {
    long long prev2 = 0;
    long long prev = 1;
    long long altura = 0;
    while (N >= 1 + prev + prev2) {
        long long actual = 1 + prev + prev2;
        prev2 = prev;
        prev = actual;
        altura++;
    }
    return altura;
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--) {
        long long N; cin >> N;
        cout << altura_minima(N) << " " << altura_maxima(N) << endl;
    }
}
