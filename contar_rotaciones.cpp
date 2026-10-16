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
            data(data), height(height), left(left), right(right), parent(parent) {}
    };

    TreeNode* root;
    int rot_count = 0; // Contador de rotaciones por operación

    AVL() {
        root = nullptr;
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u->height;
    }

    void update(TreeNode* u) {
        u->height = 1 + max(h(u->left), h(u->right));
    }

    int FB(TreeNode* u) {
        return h(u->left) - h(u->right);
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Rotación Izquierda
    TreeNode* rotate_left(TreeNode* u) {
        rot_count++;
        TreeNode* v = u->right;

        u->right = v->left;
        if (v->left != nullptr) {
            v->left->parent = u;
        }

        v->parent = u->parent;
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }

        v->left = u;
        u->parent = v;

        update(u);
        update(v);
        return v;
    }

    // Rotación Derecha
    TreeNode* rotate_right(TreeNode* u) {
        rot_count++;
        TreeNode* v = u->left;

        u->left = v->right;
        if (v->right != nullptr) {
            v->right->parent = u;
        }

        v->parent = u->parent;
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->right) {
            u->parent->right = v;
        } else {
            u->parent->left = v;
        }

        v->right = u;
        u->parent = v;

        update(u);
        update(v);
        return v;
    }

    // Rebalanceo siguiendo estrictamente las reglas del enunciado
    TreeNode* rebalance(TreeNode* u) {
        update(u);
        if (FB(u) > 1) {
            // L
            if (FB(u->left) < 0) { // Caso LR
                u->left = rotate_left(u->left);
            }
            return rotate_right(u); // Caso LL o LR finalizado
        }
        if (FB(u) < -1) {
            // R
            if (FB(u->right) > 0) { // Caso RL
                u->right = rotate_right(u->right);
            }
            return rotate_left(u); // Caso RR o RL finalizado
        }
        return u;
    }

    // Inserción recursiva
    TreeNode* insert(TreeNode* u, data_type value, TreeNode* p = nullptr) {
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

    int insert_and_count(data_type x) {
        rot_count = 0;
        root = insert(root, x, nullptr);
        return rot_count;
    }

    // Eliminación recursiva exacta según el enunciado
    TreeNode* erase(TreeNode* u, data_type key) {
        if (u == nullptr) return nullptr;

        if (key < u->data) {
            u->left = erase(u->left, key);
        } else if (key > u->data) {
            u->right = erase(u->right, key);
        } else {
            // Caso 1: Sin hijo izquierdo
            if (u->left == nullptr) {
                TreeNode* temp = u->right;
                if (temp != nullptr) temp->parent = u->parent;
                delete u;
                return temp;
            }
            // Caso 2: Sin hijo derecho
            else if (u->right == nullptr) {
                TreeNode* temp = u->left;
                if (temp != nullptr) temp->parent = u->parent;
                delete u;
                return temp;
            }
            // Caso 3: Dos hijos (reemplazar con el sucesor: mínimo del subárbol derecho)
            TreeNode* succ = min_element(u->right);
            u->data = succ->data;
            u->right = erase(u->right, succ->data);
        }
        return rebalance(u);
    }

    int erase_and_count(data_type x) {
        rot_count = 0;
        root = erase(root, x);
        return rot_count;
    }

    // Altura actual de la raíz (-1 si está vacío)
    int get_height() {
        return h(root);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    AVL<int> arbol;

    while (q--) {
        int op, x;
        cin >> op >> x;

        int rotaciones = 0;
        if (op == 1) {
            rotaciones = arbol.insert_and_count(x);
        } else {
            rotaciones = arbol.erase_and_count(x);
        }
        cout << rotaciones << " " << arbol.get_height() << "\n";
    }
    return 0;
}
