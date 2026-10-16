#include <iostream>
using namespace std;

const int MAX = 200005;
long long L[MAX];
long long R[MAX];
long long padre[MAX];

int main() {
    // Optimización de E/S
    cin.tie(0)->sync_with_stdio(false);

    long long n;
    cin >> n;
    long long q;
    cin >> q;

    // 1. Lectura del árbol inicial y armado de padres
    for (long long i = 1; i <= n; i++) {
        cin >> L[i] >> R[i];
        if (L[i] != 0) {
            padre[L[i]] = i;
        }
        if (R[i] != 0) {
            padre[R[i]] = i;
        }
    }

    // La raíz inicial por defecto es 1 y no tiene padre
    padre[1] = 0;
    int raiz = 1;

    // 2. Procesamiento de las q consultas de rotación
    while (q--) {
        char op;
        cin >> op;
        int x;
        cin >> x;

        if (op == 'I') { // Rotación Izquierda
            long long derecho_y = R[x];
            long long izquierdo_y = L[derecho_y];

            padre[derecho_y] = padre[x];
            if (padre[x] == 0) { // x era raíz
                raiz = derecho_y;
            } else {
                if (L[padre[x]] == x) {
                    L[padre[x]] = derecho_y;
                } else {
                    R[padre[x]] = derecho_y;
                }
            }
            // Subárbol de y
            R[x] = izquierdo_y;
            if (izquierdo_y != 0) {
                padre[izquierdo_y] = x;
            }
            L[derecho_y] = x;
            padre[x] = derecho_y;
        }
        else { // Rotación Derecha (D)
            long long izquierdo_y = L[x];
            long long derecho_de_y = R[izquierdo_y];

            padre[izquierdo_y] = padre[x];
            if (padre[x] == 0) { // x era raíz
                raiz = izquierdo_y;
            } else {
                if (L[padre[x]] == x) {
                    L[padre[x]] = izquierdo_y;
                } else {
                    R[padre[x]] = izquierdo_y;
                }
            }

            // Subárbol de y
            L[x] = derecho_de_y;
            if (derecho_de_y != 0) {
                padre[derecho_de_y] = x;
            }
            R[izquierdo_y] = x;
            padre[x] = izquierdo_y;
        }
    }

    // 3. Imprimir el resultado final requerido por el problema
    cout << raiz << "\n";
    for (int i = 1; i <= n; i++) {
        cout << L[i] << " " << R[i] << "\n";
    }

    return 0;
}
