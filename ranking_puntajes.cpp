//
// Created by Dayron Cueva on 15/10/2026.
//
#include <iostream>
using namespace std;

template<typename data_type>
struct AVL {
    struct TreeNode {
        int height;
        int size;
        data_type data;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;

        TreeNode(data_type data = data_type(), int height = 0, int size=1,
                 TreeNode* left = nullptr, TreeNode* right = nullptr, TreeNode* parent = nullptr) :
            data(data), size(size), height(height), left(left), right(right), parent(parent) {}
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
        u->size = 1 + get_size(u->left) + get_size(u->right);
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
    TreeNode* min_element() {
        return min_element(root);
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
            return new TreeNode(value, 0, 1,nullptr, nullptr, p);
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
    void erase(data_type valor) {
        root = erase(root, valor);
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

    TreeNode* get_sucesor (TreeNode* u) {
        if (u == nullptr) { return nullptr;}
        TreeNode* derecho = u->right;
        if (derecho!=nullptr) {
            return min_element(derecho);
        }
        TreeNode* padre = u->parent;
        while (padre!=nullptr && padre->right ==u) {
            u = padre;
            padre = padre->parent;
        }
        return padre;
    }
    TreeNode* max_element (TreeNode* nodo) {
        if (nodo==nullptr) {
            return nullptr;
        }
        TreeNode* current = nodo;
        while (current->right!=nullptr) {
            current = current->right;
        }
        return current;
    }
    TreeNode* get_predecesor (TreeNode* u) {
        if (u==nullptr) {return nullptr;}
        TreeNode* izq = u->left;
        if (izq!=nullptr) {
            return max_element(izq);
        }
        TreeNode* padre = u->parent;
        while (padre!=nullptr && padre->left == u) {
            u = padre;
            padre = padre->parent;
        }
        return padre;
    }
    data_type vecino_mas_cerca (data_type valor) {
        TreeNode* current =  root;
        TreeNode* mejor = root;
        int minimo  = abs(current->data-valor) ;
        while (current!=nullptr) {
            int distancia = abs(current->data-valor);
            if (distancia<minimo || (distancia==minimo && mejor!=nullptr && current->data<mejor->data)) {
                minimo = distancia;
                mejor = current;
            }

            if (valor==current->data) {
                break;
            }
            else if (valor < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        // evaluar predecesor y sucesor
        TreeNode* predecesor = get_predecesor(mejor);
        TreeNode* sucesor  = get_sucesor(mejor);
        if (predecesor!=nullptr) {
            int evaluar = abs(predecesor->data-valor);
            if (evaluar<minimo) {
                minimo=evaluar;
                mejor = predecesor;
            }
        }
        if (sucesor!=nullptr) {
            int ev = abs(sucesor->data-valor);
            if (ev<minimo) {
                minimo=ev;
                mejor = sucesor;
            }
        }
        return mejor->data;
    }
    void vecino(data_type valor) {
        int cercano= vecino_mas_cerca(valor);
        cout<<cercano<<endl;
    }
    TreeNode* successor(TreeNode* x) {
        if (x -> right != nullptr) {
            return min_element(x -> right);
        }
        TreeNode* y = x -> parent;
        while (y != nullptr and y -> right == x) {
            x = y;
            y = y -> parent;
        }
        return y;
    }
    int get_size (TreeNode* u) {
        return u == nullptr ? 0 : u -> size;
    }
    int ct_mejores_q_x (int numero) {
        TreeNode* current = root;
        int contador = 0;
        while (current!=nullptr) {
            if (current->data>=numero) {
                current=current->left;
            }
            else {
                contador += 1 + get_size(current->left);
                current=current->right;
            }
        }
        return contador;
    }
};

int main () {
    cin.tie(0)->sync_with_stdio(false);
    int q;
    cin>>q;
    AVL<int> rankings;
    while (q--) {
        int op; cin>> op;
        if (op==1) {
            int numero;
            cin>> numero;
            rankings.insert(numero);
        }
        else {
            int x; cin>>x;
            cout<<rankings.ct_mejores_q_x(x)<<'\n';
        }
    }
    return 0;
}
