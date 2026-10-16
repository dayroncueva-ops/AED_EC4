#include <iostream>
using namespace std;

template<typename data_type>
struct AVL {
    struct TreeNode {
        int height;
        data_type data;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        TreeNode(data_type data = data_type(), int height = 0,
        TreeNode* left = nullptr, TreeNode* right = nullptr, TreeNode* parent = nullptr) :
        data(data), height(height), left(left), right(right), parent(parent){}
    };

    TreeNode* root;
    AVL() { root = nullptr; }

    void update(TreeNode* u) {
        u->height = 1 + max(h(u->left), h(u->right));
    }
    int h(TreeNode* u) {
        return u == nullptr ? -1 : u->height;
    }
    int FB(TreeNode* u) {
        return h(u->left) - h(u->right);
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current->left != nullptr) current = current->left;
        return current;
    }

    TreeNode* max_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current->right != nullptr) current = current->right;
        return current;
    }

    TreeNode* max_element() {
        return max_element(root);
    }

    TreeNode* rotate_left(TreeNode* u) {
        TreeNode* v = u->right;
        u->right = v->left;
        if (v->left != nullptr) v->left->parent = u;
        v->parent = u->parent;
        v->left = u;
        u->parent = v;
        update(u);
        update(v);
        return v;
    }

    TreeNode* rotate_right(TreeNode* u) {
        TreeNode* v = u->left;
        u->left = v->right;
        if (v->right != nullptr) v->right->parent = u;
        v->parent = u->parent;
        v->right = u;
        u->parent = v;
        update(u);
        update(v);
        return v;
    }

    TreeNode* rebalance(TreeNode* u) {
        update(u);
        if (FB(u) > 1) {
            if (FB(u->left) < 0) {
                u->left = rotate_left(u->left);
            }
            return rotate_right(u);
        }
        if (FB(u) < -1) {
            if (FB(u->right) > 0) {
                u->right = rotate_right(u->right);
            }
            return rotate_left(u);
        }
        return u;
    }

    TreeNode* insert(TreeNode* u, data_type value, TreeNode* p) {
        if (u == nullptr) {
            return new TreeNode(value, 0, nullptr, nullptr, p);
        }
        if (value < u->data) {
            u->left = insert(u->left, value, u);
        } else {
            u->right = insert(u->right, value, u);
        }
        return rebalance(u);
    }

    void insert(data_type value) {
        root = insert(root, value, nullptr);
    }

    TreeNode* erase(TreeNode* u, data_type key) {
        if (u == nullptr) return nullptr;

        if (key < u->data) {
            u->left = erase(u->left, key);
        } else if (key > u->data) {
            u->right = erase(u->right, key);
        } else {
            if (u->left == nullptr) {
                TreeNode* temp = u->right;
                if (temp != nullptr) temp->parent = u->parent;
                delete u;
                return temp;
            } else if (u->right == nullptr) {
                TreeNode* temp = u->left;
                if (temp != nullptr) temp->parent = u->parent;
                delete u;
                return temp;
            }
            TreeNode* succ = min_element(u->right);
            u->data = succ->data;
            u->right = erase(u->right, succ->data);
        }
        return rebalance(u);
    }

    void erase(data_type valor) {
        root = erase(root, valor);
    }

    TreeNode* buscar_nodo(int cancion) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current->data.first < cancion) {
                current = current->right;
            } else if (current->data.first > cancion) {
                current = current->left;
            } else {
                return current;
            }
        }
        return nullptr;
    }

    // OPERACIÓN 3 ULTRA RÁPIDA EN O(log n): El máximo de arbol2 ya tiene al ganador
    void mas_votos() {
        TreeNode* ganador = max_element();
        if (ganador != nullptr) {
            int frecuencia = ganador->data.first;
            int id_cancion = -ganador->data.second; // Recuperamos el ID positivo
            cout << id_cancion << " " << frecuencia << "\n";
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(istream::badbit | istream::failbit);

    AVL<pair<int, int>> arbol1; // {id_cancion, frecuencia}
    AVL<pair<int, int>> arbol2; // {frecuencia, -id_cancion} para desempate automático

    long long q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int id_cancion;
            cin >> id_cancion;
            auto nodo = arbol1.buscar_nodo(id_cancion);
            if (nodo == nullptr) {
                arbol1.insert({id_cancion, 1});
                arbol2.insert({1, -id_cancion}); // Guardamos ID negativo
            } else {
                int frecuencia = nodo->data.second;
                arbol2.erase({frecuencia, -id_cancion});
                nodo->data.second++;
                arbol2.insert({frecuencia + 1, -id_cancion});
            }
        } else if (op == 2) {
            int x;
            cin >> x;
            auto nodito = arbol1.buscar_nodo(x);
            int frec = nodito->data.second;
            arbol2.erase({frec, -x});
            if (frec == 1) {
                arbol1.erase({x, 1});
            } else {
                nodito->data.second--;
                arbol2.insert({frec - 1, -x});
            }
        } else {
            arbol2.mas_votos();
        }
    }
    return 0;
}
