//
// Created by Timana on 16/10/2026.
//
#include <bits/stdc++.h>
using namespace std;

void f(int n, int maximo, vector<int>& v) {
    if (n == 0) {
        for (int x : v) {
            cout << x << " ";
        }
        cout << "\n";
        return;
    }

    for (int i = min(n, maximo); i >= 1; i--) {
        v.push_back(i);

        f(n - i, i, v);

        v.pop_back();
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> v;

    f(n, n, v);

    return 0;
}