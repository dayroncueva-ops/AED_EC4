#include <bits/stdc++.h>
using namespace std;

template<typename data_type>
struct BST {

    struct TreeNode {
        data_type data;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        int altura;
        long long suma;

        TreeNode(data_type data = data_type(),
                 TreeNode* left = nullptr,
                 TreeNode* right = nullptr,
                 TreeNode* parent = nullptr)
            : data(data), left(left), right(right),
              parent(parent), altura(0), suma(data.second){}
    };

    TreeNode* root;

    BST() {
        root = nullptr;
    }

    ~BST() {
        clear(root);
    }

    void clear(TreeNode* u) {
        if (u == nullptr) return;
        clear(u->left);
        clear(u->right);
        delete u;
    }

    long long suma_v(TreeNode* u) {
        if (u == nullptr) return 0;
        return u->suma;
    }

    // BUSQUEDA
    bool search(data_type key) {
        TreeNode* current = root;

        while (current != nullptr) {
            if (current->data == key) {
                return true;
            }

            if (current->data > key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return false;
    }

    // MINIMO Y MAXIMO
    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;

        TreeNode* current = u;

        while (current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    TreeNode* max_element(TreeNode* u) {
        if (u == nullptr) return nullptr;

        TreeNode* current = u;

        while (current->right != nullptr) {
            current = current->right;
        }

        return current;
    }

    TreeNode* min_element() {
        return min_element(root);
    }

    TreeNode* max_element() {
        return max_element(root);
    }

    // RECORRIDOS
    void print_inorder() {
        print_subtree_inorder(root);
        cout << endl;
    }

    void print_subtree_inorder(TreeNode* u) {
        if (u == nullptr) return;

        print_subtree_inorder(u->left);
        cout << u->data << " ";
        print_subtree_inorder(u->right);
    }

    void print_preorder() {
        print_subtree_preorder(root);
        cout << endl;
    }

    void print_subtree_preorder(TreeNode* u) {
        if (u == nullptr) return;

        cout << u->data << " ";
        print_subtree_preorder(u->left);
        print_subtree_preorder(u->right);
    }

    void print_postorder() {
        print_subtree_postorder(root);
        cout << endl;
    }

    void print_subtree_postorder(TreeNode* u) {
        if (u == nullptr) return;

        print_subtree_postorder(u->left);
        print_subtree_postorder(u->right);
        cout << u->data << " ";
    }

    // SUCESOR
    TreeNode* successor(TreeNode* x) {
        if (x == nullptr) return nullptr;

        if (x->right != nullptr) {
            return min_element(x->right);
        }

        TreeNode* y = x->parent;

        while (y != nullptr && y->right == x) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    // PREDECESOR
    TreeNode* predecessor(TreeNode* x) {
        if (x == nullptr) return nullptr;

        if (x->left != nullptr) {
            return max_element(x->left);
        }

        TreeNode* y = x->parent;

        while (y != nullptr && y->left == x) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    // ALTURA
    int altura_v(TreeNode* u) {
        if (u == nullptr) return -1;
        return u->altura;
    }

    void actualizar_altura(TreeNode* v) {
        if (v == nullptr) return;

        v->altura = 1 + max(
            altura_v(v->left),
            altura_v(v->right)
        );

        v->suma = suma_v(v->left)
                + suma_v(v->right)
                + v->data.second;
    }

    // FACTOR DE BALANCE
    int Factor_de_balance(TreeNode* v) {
        if (v == nullptr) return 0;

        return altura_v(v->left) - altura_v(v->right);
    }

    // ROTACION DERECHA
    TreeNode* rotate_right(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;
        TreeNode* padre = y->parent;

        x->right = y;
        y->left = T2;

        x->parent = padre;
        y->parent = x;

        if (T2 != nullptr) {
            T2->parent = y;
        }

        actualizar_altura(y);
        actualizar_altura(x);

        return x;
    }

    // ROTACION IZQUIERDA
    TreeNode* rotate_left(TreeNode* y) {
        TreeNode* x = y->right;
        TreeNode* T2 = x->left;
        TreeNode* padre = y->parent;

        x->left = y;
        y->right = T2;

        x->parent = padre;
        y->parent = x;

        if (T2 != nullptr) {
            T2->parent = y;
        }

        actualizar_altura(y);
        actualizar_altura(x);

        return x;
    }

    // REBALANCEO
    TreeNode* revalance(TreeNode* v) {
        if (v == nullptr) return nullptr;

        actualizar_altura(v);

        if (Factor_de_balance(v) > 1) {

            if (Factor_de_balance(v->left) < 0) {
                v->left = rotate_left(v->left); // LR
                v->left->parent = v;
            }

            return rotate_right(v); // LL
        }

        if (Factor_de_balance(v) < -1) {

            if (Factor_de_balance(v->right) > 0) {
                v->right = rotate_right(v->right); // RL
                v->right->parent = v;
            }

            return rotate_left(v); // RR
        }

        return v;
    }

    // INSERCION
    TreeNode* insert(TreeNode* u, data_type key) {
        if (u == nullptr) {
            return new TreeNode(key);
        }

        if (key < u->data) {
            u->left = insert(u->left, key);

            if (u->left != nullptr) {
                u->left->parent = u;
            }
        }
        else if (key > u->data) {
            u->right = insert(u->right, key);

            if (u->right != nullptr) {
                u->right->parent = u;
            }
        }
        else {
            return u; // No insertar duplicados
        }

        return revalance(u);
    }

    // ELIMINACION
    TreeNode* eliminar(TreeNode* u, data_type key) {
        if (u == nullptr) return nullptr;

        if (key < u->data) {
            u->left = eliminar(u->left, key);

            if (u->left != nullptr) {
                u->left->parent = u;
            }
        }
        else if (key > u->data) {
            u->right = eliminar(u->right, key);

            if (u->right != nullptr) {
                u->right->parent = u;
            }
        }
        else {
            // Caso 1 y 2: cero o un hijo
            if (u->left == nullptr || u->right == nullptr) {

                TreeNode* temp = (u->left != nullptr)
                                 ? u->left
                                 : u->right;

                if (temp != nullptr) {
                    temp->parent = u->parent;
                }

                delete u;
                return temp;
            }

            // Caso 3: dos hijos
            TreeNode* s = min_element(u->right);

            u->data = s->data;

            u->right = eliminar(u->right, s->data);

            if (u->right != nullptr) {
                u->right->parent = u;
            }
        }

        return revalance(u);
    }

    // FUNCIONES PUBLICAS PARA INSERTAR Y ELIMINAR
    void insertar(data_type key) {
        root = insert(root, key);

        if (root != nullptr) {
            root->parent = nullptr;
        }
    }

    void borrar(data_type key) {
        root = eliminar(root, key);

        if (root != nullptr) {
            root->parent = nullptr;
        }
    }

    long long suma_aux(TreeNode* u, long long x) {
        if (u == nullptr) return 0;

        if (u->data.first > x) {
            return suma_aux(u->left, x);
        }

        return suma_v(u->left) +
               u->data.second
               + suma_aux(u->right, x);
    }

    long long sumar(long long l, long long r) {
        return suma_aux(root, r) - suma_aux(root, l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long q;
    cin >> q;

    BST<pair<int, long long>> AVL;
    unordered_map<long long, int> votos;

    while (q--) {
        int n; cin >> n;

        if (n == 1) {
            long long x;
            cin >> x;

            int cantidad_de_productos = votos[x];

            if (cantidad_de_productos > 0) {
                AVL.borrar({x, cantidad_de_productos});
            }

            votos[x]++;

            AVL.insertar({x, votos[x]});
        }

        else if (n==2) {
            long long x; cin >> x;

            int cantidad_de_productos = votos[x];

            votos[x]--;
            AVL.borrar({x, cantidad_de_productos});

            if (votos[x] > 0) {
                AVL.insertar({x, votos[x]});
            }
        }


        else if (n==3){
            long long l; cin >> l;
            long long r; cin >> r;
            cout << AVL.sumar(l, r) << endl;
        }
    }

    return 0;
}