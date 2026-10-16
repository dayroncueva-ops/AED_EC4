//
// Created by Dayron Cueva on 13/10/2026.
//
#include <iostream>
#include <vector>
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
        TreeNode* left = nullptr,
        TreeNode* right = nullptr,
        TreeNode* parent = nullptr) :
        data(data), height(height), left(left), right(right), parent(parent){}
        };
        TreeNode* root;
        AVL() {
            root = nullptr;
        }
        void update(TreeNode* u) {
            u -> height = 1 + max(h(u -> left) , h(u -> right));
        }
        int h(TreeNode* u) {
            return u == nullptr ? -1 : u -> height;
        }
        int FB(TreeNode* u) {
            return h(u -> left) - h(u -> right);
        }
        bool search(data_type key) {
            TreeNode* current = root;
            while (current != nullptr) {
                if (current->data == key) {
                    return true;
                }
                if (current -> data > key) {
                    current = current -> left;
                }
                else {
                    current = current -> right;
                }
            }
            return false;
        }
        TreeNode* min_element(TreeNode* u) {
            if (u == nullptr) return nullptr;
            TreeNode* current = u;
            while (current -> left != nullptr) {
                current = current -> left;
            }
            return current;
        }
        TreeNode* max_element(TreeNode* u) {
            if (u == nullptr) return nullptr;
            TreeNode* current = u;
            while (current -> right != nullptr) {
                current = current -> right;
            }
            return current;
        }
        TreeNode* min_element() {
            return min_element(root);
        }
        TreeNode* max_element() {
            return max_element(root);
        }
        TreeNode* rotate_left(TreeNode* u) {
            TreeNode* v = u -> right;
            u -> right = v -> left;
            v -> left = u;
            update(u);
            update(v);
            return v;
        }
        TreeNode* rotate_right(TreeNode* u) {
            TreeNode* v = u -> left;
            u -> left = v -> right;
            v -> right = u;
            update(u);
            update(v);
            return v;
        }
        TreeNode* rebalance(TreeNode* u) {
            update(u);
            if (FB(u) > 1) {
            // L
                if (FB(u -> left) < 0) {
                // LR
                u -> left = rotate_left(u -> left);
                }
                return rotate_right(u);
            }
            if (FB(u) < -1) {
            // R
                if (FB(u -> right) > 0) {
                // RL
                    u -> right = rotate_right(u -> right);
                }
                return rotate_left(u);
            }
            return u;
        }
        TreeNode* insert(TreeNode* u, data_type value,TreeNode* p) {
            if (u == nullptr) {
                return new TreeNode(value, 0,nullptr, nullptr,p);
            }
            if (value < u -> data) {
                u -> left = insert(u -> left, value,u);
            }
            else {
                u -> right = insert(u -> right, value,u);
            }
            return rebalance(u);
        }
        void insert(data_type value) {
            root = insert(root, value,nullptr);
        }
        void print_inorder() {
            print_subtree_inorder(root);
            cout << endl;
        }
        void print_subtree_inorder(TreeNode* u) {
            if (u == nullptr) return;
            print_subtree_inorder(u -> left);
            cout << u -> data << " ";
            print_subtree_inorder(u -> right);
        }
        void print_preorder() {
            print_subtree_preorder(root);
            cout << endl;
        }
        void print_subtree_preorder(TreeNode* u) {
            if (u == nullptr) return;
            cout << u -> data << " ";
            print_subtree_preorder(u -> left);
            print_subtree_preorder(u -> right);
        }
        void print_postorder() {
            print_subtree_postorder(root);
            cout << endl;
        }
        void print_subtree_postorder(TreeNode* u) {
            if (u == nullptr) return;
            print_subtree_postorder(u -> left);
            print_subtree_postorder(u -> right);
            cout << u -> data << " ";
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
        TreeNode* predecessor(TreeNode* x) {
            if (x -> left != nullptr) {
                return max_element(x -> left);
            }
            TreeNode* y = x -> parent;
            while (y != nullptr and y -> left == x) {
                x = y;
                y = y -> parent;
            }
            return y;
        }
        TreeNode* transplant(TreeNode* u, TreeNode* v) {
            if (u -> parent == nullptr) {
                root = v;
            }
            else if (u -> parent -> right == u) {
                u -> parent -> right = v;
            }
            else {
                u -> parent -> left = v;
            }
            if (v != nullptr) {
                v -> parent = u -> parent;
            }
            delete u;
        }
        TreeNode* erase(TreeNode* u) {
            return nullptr;
        }
        TreeNode* buscar (TreeNode* u, data_type key) {
            if (u==nullptr) { return nullptr;}
            TreeNode* current =  u;
            while (current!=nullptr) {
                if (current->data==key) {
                    return current;
                }

                else if (current->data>key) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }
            return nullptr;
        }
        TreeNode* buscar_nodo (data_type x) {
            return buscar(root,x);
        }
        data_type get_raiz() {
            if (root==nullptr) return -1;
            return root->data;
        }
        data_type get_height () {
            if (root==nullptr) return -1;
            return root->height;
        }
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
        TreeNode* predecesor_cercano (int s) {
            TreeNode* current = root;
            TreeNode* candidato = nullptr;
            while (current!=nullptr) {
                if (current->data.first<=s) {
                    candidato = current;
                    current= current->right;
                }
                else {
                    current = current->left;
                }
            }
            return candidato;
        }
        TreeNode* sucesor_cercano (int s) {
            TreeNode* current = root;
            TreeNode* candidato = nullptr;
                // s,e
            while (current!=nullptr) {
                if (current->data.first>=s) {
                    candidato = current;
                    current = current->left;
                } // 4,6 4,
                else {
                    current = current->right;
                }
            }
            return candidato;
        }
        void eliminar_reserva (int nodo) {
            TreeNode* nodo_encontrado = buscar_nodito(nodo);
            erase(nodo_encontrado->data);

        }
        TreeNode* buscar_nodito(int nodo) {
            TreeNode* current =  root;
            while (current!=nullptr) {
                if (current->data.first == nodo) {
                    return current;
                }
                else if (current->data.first<=nodo) {
                    current = current->right;
                }
                else {
                    current = current->left;
                }
            }
            return nullptr;
        }

};

int main () {
    int q;
    cin>> q;
    AVL<pair<int,int>> arbol;
    while (q--) {
        char op;
        cin>> op;
        bool choca = false;
        if (op=='1') {
            int s, e;
            cin>> s >> e;
            auto predecesor = arbol.predecesor_cercano(s);
            if (predecesor!= nullptr) {
                if (predecesor->data.second>s) {
                    choca = true;
                }
            } // s, e 4, 6   6
            auto sucesor = arbol.sucesor_cercano(s);
            if (sucesor!= nullptr) {
                if (sucesor->data.first<e) {
                    choca = true;
                }
            }
            if (choca) {
                cout<<"NO"<<endl;
            }
            else {
                cout<<"SI"<<endl;
                arbol.insert(pair<int,int>(s,e));
            }
        }
        else if (op=='2') {
            int s;
            cin>>s;
            arbol.eliminar_reserva(s);
        }
        else {
            int t;
            cin>> t;
            auto nodo_bucado = arbol.predecesor_cercano(t);

            if (nodo_bucado!=nullptr && nodo_bucado->data.first<=t && nodo_bucado->data.second>t) {
                cout<<nodo_bucado->data.first<<" "<<nodo_bucado->data.second<<endl;
            }
            else {
                cout<<"LIBRE"<<endl;
            }
        }
    }
    return 0;
}
