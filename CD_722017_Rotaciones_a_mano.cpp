
#include <bits/stdc++.h>
using namespace std;

long long rotate_left_segun_vector(int key, vector<vector<long long>>& v, vector<long long>& parent) {
    long long indice = key - 1;
    long long indice_right = v[indice][1] - 1;
    long long padre = parent[indice];

    v[indice][1] = v[indice_right][0];

    if (v[indice_right][0] != 0) {
        parent[v[indice_right][0] - 1] = key;
    }

    v[indice_right][0] = key;
    parent[indice] = indice_right + 1;
    parent[indice_right] = padre;

    if (padre != 0) {
        if (v[padre - 1][0] == key) {
            v[padre - 1][0] = indice_right + 1;
        } else {
            v[padre - 1][1] = indice_right + 1;
        }
    }

    return indice_right + 1;
}

long long rotate_right_segun_vector(int key, vector<vector<long long>>& v, vector<long long>& parent) {
    long long indice = key - 1;
    long long indice_left = v[indice][0] - 1;
    long long padre = parent[indice];

    v[indice][0] = v[indice_left][1];

    if (v[indice_left][1] != 0) {
        parent[v[indice_left][1] - 1] = key;
    }

    v[indice_left][1] = key;
    parent[indice] = indice_left + 1;
    parent[indice_left] = padre;

    if (padre != 0) {
        if (v[padre - 1][0] == key) {
            v[padre - 1][0] = indice_left + 1;
        } else {
            v[padre - 1][1] = indice_left + 1;
        }
    }

    return indice_left + 1;
}

void inprimir(vector<vector<long long>>& v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j];
            if (j != v[i].size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    long long n; cin >> n;
    long long q; cin >> q;

    vector<vector<long long>> v(n, vector<long long>(2));
    vector<long long> parent(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> v[i][0];
        cin >> v[i][1];

        if (v[i][0] != 0) parent[v[i][0] - 1] = i + 1;
        if (v[i][1] != 0) parent[v[i][1] - 1] = i + 1;
    }

    long long raiz = 1;

    while (q--) {
        char c; cin >> c;
        long long n; cin >> n;

        if (c == 'I') {
            long long nuevo = rotate_left_segun_vector(n, v, parent);
            if (raiz == n) raiz = nuevo;
        }
        if (c == 'D') {
            long long nuevo = rotate_right_segun_vector(n, v, parent);
            if (raiz == n) raiz = nuevo;
        }
    }

    cout << raiz << endl;
    inprimir(v);
}
