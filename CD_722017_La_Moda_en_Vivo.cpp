#include <bits/stdc++.h>
using namespace std;

template<typename data_type>
struct BST {

    struct TreeNode {
        data_type data;
        TreeNode* left;
        TreeNode* right;
        int altura;

        TreeNode(data_type data)
            : data(data), left(nullptr), right(nullptr), altura(0) {}
    };

    TreeNode* root = nullptr;

    int altura_v(TreeNode* u) {
        if (u == nullptr) return -1;
        return u->altura;
    }

    void actualizar_altura(TreeNode* u) {
        if (u == nullptr) return;

        u->altura = 1 + max(
            altura_v(u->left),
            altura_v(u->right)
        );
    }

    int Factor_de_balance(TreeNode* u) {
        if (u == nullptr) return 0;

        return altura_v(u->left) - altura_v(u->right);
    }

    TreeNode* rotate_right(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        actualizar_altura(y);
        actualizar_altura(x);

        return x;
    }

    TreeNode* rotate_left(TreeNode* y) {
        TreeNode* x = y->right;
        TreeNode* T2 = x->left;

        x->left = y;
        y->right = T2;

        actualizar_altura(y);
        actualizar_altura(x);

        return x;
    }

    TreeNode* revalance(TreeNode* u) {
        if (u == nullptr) return nullptr;

        actualizar_altura(u);

        if (Factor_de_balance(u) > 1) {
            if (Factor_de_balance(u->left) < 0) {
                u->left = rotate_left(u->left);
            }
            return rotate_right(u);
        }

        if (Factor_de_balance(u) < -1) {
            if (Factor_de_balance(u->right) > 0) {
                u->right = rotate_right(u->right);
            }
            return rotate_left(u);
        }

        return u;
    }

    TreeNode* insert(TreeNode* u, data_type key) {
        if (u == nullptr) {
            return new TreeNode(key);
        }

        if (key < u->data) {
            u->left = insert(u->left, key);
        }
        else if (key > u->data) {
            u->right = insert(u->right, key);
        }
        else {
            return u;
        }

        return revalance(u);
    }

    TreeNode* min_element(TreeNode* u) {
        while (u != nullptr && u->left != nullptr) {
            u = u->left;
        }
        return u;
    }

    TreeNode* max_element(TreeNode* u) {
        while (u != nullptr && u->right != nullptr) {
            u = u->right;
        }
        return u;
    }

    TreeNode* max_element() {
        return max_element(root);
    }

    TreeNode* eliminar(TreeNode* u, data_type key) {
        if (u == nullptr) return nullptr;

        if (key < u->data) {
            u->left = eliminar(u->left, key);
        }
        else if (key > u->data) {
            u->right = eliminar(u->right, key);
        }
        else {
            if (u->left == nullptr || u->right == nullptr) {
                TreeNode* temp = (u->left != nullptr)
                                 ? u->left : u->right;

                delete u;
                return temp;
            }

            TreeNode* s = min_element(u->right);
            u->data = s->data;
            u->right = eliminar(u->right, s->data);
        }

        return revalance(u);
    }

    void insertar(data_type key) {
        root = insert(root, key);
    }

    void borrar(data_type key) {
        root = eliminar(root, key);
    }

    void clear(TreeNode* u) {
        if (u == nullptr) return;
        clear(u->left);
        clear(u->right);
        delete u;
    }

    ~BST() {
        clear(root);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    BST<pair<int, long long>> AVL;
    unordered_map<long long, int> votos;

    while (q--) {
        int tipo;
        cin >> tipo;

        if (tipo == 1) {
            long long x;
            cin >> x;

            int anterior = votos[x];

            if (anterior > 0) {
                AVL.borrar({anterior, -x});
            }

            votos[x]++;

            AVL.insertar({votos[x], -x});
        }
        else if (tipo == 2) {
            long long x;
            cin >> x;

            int anterior = votos[x];

            AVL.borrar({anterior, -x});

            votos[x]--;

            if (votos[x] > 0) {
                AVL.insertar({votos[x], -x});
            }
        }
        else if (tipo == 3) {
            auto* ganador = AVL.max_element();

            cout << -ganador->data.second << " "
                 << ganador->data.first << '\n';
        }
    }

    return 0;
}