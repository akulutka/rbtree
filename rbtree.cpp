#include <iostream>
#include <memory>

struct Node {
    Node* l;
    Node* r;
    Node* p;
    int key;
    bool color;
    explicit Node(int x) {
        key = x;
        color = true;
        l = nullptr;
        r = nullptr;
        p = nullptr;
    }
};

class RedBlack {
 private:
    Node* root;
    size_t _size;

    void print_node(Node* ptr) {
        if (ptr == nullptr) {
            return;
        }
        print_node(ptr->l);
        std::cout << ptr->key << " ";
        if (ptr->l == nullptr) {
            std::cout << "null ";
        } else {
            std::cout << ptr->l->key << " ";
        }
        if (ptr->r == nullptr) {
            std::cout << "null ";
        } else {
            std::cout << ptr->r->key << " ";
        }
        if (ptr->color) {
            std::cout << "R\n";
        } else {
            std::cout << "B\n";
        }
        print_node(ptr->r);
    }

    void lrot(Node* x) {
        Node* y = x->r;
        x->r = y->l;
        if (y->l != nullptr) {
            y->l->p = x;
        }
        y->p = x->p;
        if (x->p == nullptr) {
            root = y;
        } else if (x == x->p->l) {
            x->p->l = y;
        } else {
            x->p->r = y;
        }
        y->l = x;
        x->p = y;
    }

    void rrot(Node* x) {
        Node* y = x->l;
        x->l = y->r;
        if (y->r != nullptr) {
            y->r->p = x;
        }
        y->p = x->p;
        if (x->p == nullptr) {
            root = y;
        } else if (x == x->p->r) {
            x->p->r = y;
        } else {
            x->p->l = y;
        }
        y->r = x;
        x->p = y;
    }

    void fix(Node* x) {
        Node* u;
        while (x->color && x->p->color) {
            if (x->p == x->p->p->r) {
                u = x->p->p->l;
                if (u != nullptr && u->color) {
                    u->color = 0;
                    x->p->color = 0;
                    x->p->p->color = 1;
                    x = x->p->p;
                } else {
                    if (x == x->p->l) {
                        x = x->p;
                        rrot(x);
                    }
                    x->p->color = 0;
                    x->p->p->color = 1;
                    lrot(x->p->p);
                }
            } else {
                u = x->p->p->r;
                if (u != nullptr && u->color) {
                    u->color = 0;
                    x->p->color = 0;
                    x->p->p->color = 1;
                    x = x->p->p;
                } else {
                    if (x == x->p->r) {
                        x = x->p;
                        lrot(x);
                    }
                    x->p->color = 0;
                    x->p->p->color = 1;
                    rrot(x->p->p);
                }
            }
            if (x == root) {
                break;
            }
        }
        root->color = 0;
    }

 public:
    RedBlack() {
        root = nullptr;
        _size = 0;
    }

    void print() {
        print_node(root);
    }

    size_t size() {
        return _size;
    }

    void insert(int x) {
        ++_size;
        Node* nnode = new Node(x);
        if (root == nullptr) {
            root = nnode;
            root->color = 0;
            return;
        }
        Node* nde = root;
        bool right = false;
        while (nde != nullptr) {
            if (nnode->key > nde->key) {
                if (nde->r == nullptr) {
                    right = true;
                    break;
                }
                nde = nde->r;
            } else {
                if (nde->l == nullptr) {
                    break;
                }
                nde = nde->l;
            }
        }
        nnode->p = nde;
        if (right) {
            nnode->p->r = nnode;
        } else {
            nnode->p->l = nnode;
        }
        fix(nnode);
    }

    bool has(int x) {
        Node* nde = root;
        while (nde != nullptr) {
            if (x == nde->key) {
                return true;
            }
            if (x > nde->key) {
                nde = nde->r;
            } else {
                nde = nde->l;
            }
        }
        return false;
    }
};

int main() {
    RedBlack tree;
    int qrys;
    int qry, arg;
    std::cin >> qrys;
    for (int i = 0; i < qrys; ++i) {
        std::cin >> qry >> arg;
        if (qry == 0) {
            if (!tree.has(arg)) {
                tree.insert(arg);
            }
        } else {
            if (tree.has(arg)) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }
    std::cout << tree.size() << "\n";
    tree.print();
    return 0;
}
