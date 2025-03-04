#include <initializer_list>
#include <algorithm>
#include <iterator>
#include <stack>

template <typename T>
struct Node {
    T key;
    Node* left;
    Node* right;
    Node* parent;
    int height;

    Node(const T& key, Node* parent = nullptr) : key(key), left(nullptr), right(nullptr), parent(parent), height(1) {}
};

template <typename T>
class AVLTree {
    public:
        class iterator {
            public:
                using value_type = T;
                using reference = T&;
                using pointer = T*;
                using iterator_category = std::bidirectional_iterator_tag;
                using difference_type = std::ptrdiff_t;

                iterator() : node_(nullptr), tree_(nullptr) {}
                iterator(Node<T>* node, const AVLTree<T>* tree) : node_(node), tree_(tree) {}

                reference operator*() const {
                    return node_->key;
                }
                pointer operator->() const {
                    return &(node->key);
                }

                interator& operator++() {
                    if (node_ == nullptr)
                        return *this
                    if (node_->right != nullptr) {
                        node_ = minimum(node_->right);
                    } else {
                        Node<T>* p = node_->parent;
                        while (p != nullptr and node_ != p->right) {
                            node_ = p;
                            p = p->parent;
                        }
                        node_ = p;
                    }
                    return *this;
                }


                iterator& operator--() {
                    if (node_ == nullptr) {
                        node_ = maximim(tree_->root_);
                    } else if (node->left != nullptr) {
                        node_ = maximim(node->left); 
                    } else {
                        Node<T>* p = node_->parent;
                        while (p != nullptr && node_ == p->left) {
                            node_ = p;
                            p = p->parent;
                        }
                        node_ = p;
                    }
                    return *this;
                }

                bool operator==(const iterator & other) const {
                    return node_ == other.node_;
                }

                bool operator!=(const iterator & other) const {
                    return !(*this == other);
                }

            private:
                Node<T>* node_;
                const AVLTree<T>* tree_;
                friend class AVLTree<T>;

                Node<T> minimum(Node<T>* node) const {
                    while (node and node->right != nullptr) 
                        node == node->left;
                    return node;
                }

                Node<T> maximim(Node<T>* node) const {
                    while (node and node->right != nullptr)
                        node = node->right;
                    return node;
                }
        };

        //конструкторы
        AVLTree(): root_(nullptr) {}

        AVLTree(std::initializer_list<T> const &items) {
            for (auto it = items.begin(); it != items.end(); ++it) {
                root_ = insert(root_, *it, nullptr);
            }
        }

        AVLTree(const AVLTree &other) : root_(copyTree(other.root_, nullptr)) {}

        iterator insert(const T& key) {
            Node<T>* insertedNode = nullptr;
            root_ = insert(root_, key, nullptr, &insertedNode);
            return iterator(insertedNode, this);
        }

        void remove(const T& key){ //удаление первого элемента с заданным ключем
            root_ = remove(root_, key, nullptr);
        }

        void erase(iterator pos) { //удаление конкретного элемента
            if (pos == end())
                return;
            root_ = eraseNode(root_, pos.node_, nullptr);
        }

        bool contains(const T& key) {
            return search(root_, key);
        }

        iterator begin() const {
            return iterator(minimum(root_), this);
        }

        iterator end() const  {
            return iterator(nullptr, this);
        }

        ~AVLTree() {
            destroy(root_);            
        }
    private:
        Node<T>* root_;  

        Node<T>* copyTree(Node<T>* node, Node<T>* parent) {
            if (!node) 
                return nullptr;
            Node<T>* newNode = new Node<T>(node->key, parent);
            newNode->left = copyTree(node->left, newNode);
            newNode->right = copyTree(node->right, newNode);
            newNode->height = node->height;
            return newNode;
        }

        void destroy(Node<T>* node) {
            if (node) {
                destroy(node->left);
                destroy(node->right);
                delete node;
            }
        }

        int height(Node<T>* node) {
            return node ? node->height: 0;
        }
        
        int getBalance(Node<T>* node) {
            return node ? (height(node->left) - height(node->right)) : 0;
        }

        Node<T>* rotateRight(Node<T>* y) {
            Node<T>* x = y->left;
            Node<T>* T2 = x->right;
            
            x->right = y;
            y->left = T2;

            x->parent = y->parent;
            y->parent = x;
            if (T2)
                T2->parent = y;

            y->height = std::max(height(y->left), height(y->right)) + 1;
            x->height = std::max(height(x->left), height(x->right)) + 1;
            return x;
        } 

        Node<T>* rotateLeft(Node<T>* x) {
            Node<T>* y = x->right;
            Node<T>* T2 = y->left;

            y->left = x;
            x->right = T2;

            y->parent = x->parent;
            x->parent = y;
            
            if (T2)
                T2->parent = x;

            y->height = std::max(height(y->left), height(y->right)) + 1;
            x->height = std::max(height(x->left), height(x->right)) + 1;
            return x;
        }

        Node<T>* minValueNode(Node<T> *node) {
            Node<T>* current = node;
            while (current && current->left != nullptr) {
                current = current->left;
            }
            return current; 
        }

        Node<T>* balance(Node<T>* node) {
            int balanceFactor = getBalance(node);
            // Left Left
            if (balanceFactor > 1 && getBalance(node->left) >= 0) {
                return rotateRight(node);
            }
            // Left Right
            if (balanceFactor > 1 && getBalance(node->left) < 0) {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            // Right Right
            if (balanceFactor < -1 && getBalance(node->right) <= 0) {
                return rotateLeft(node);
            }
            // Right Left
            if (balanceFactor < -1 && getBalance(node->right) > 0) {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            return node;
        }

        Node<T>* insert(Node<T>* node, const T& key, Node<T>* parent, Node<T>** inserted_node) {
            if (node == nullptr) {
                *inserted_node = new Node<T>(key, parent);
                return *inserted_node; 
            }
            if (key < node->key) {
                node->left = insert(node->left, key, node, inserted_node);
            } else {
                node->right = insert(node->right, key, node, inserted_node);
            }
            node->height = std::max(height(node->left), height(node->right)) + 1;
            return balance(node);
        } 

        //удаляет по указателю
        Node<T>* eraseNode(Node<T>* root, Node<T>* target, Node<T>* parent) {
            if (root == nullptr)
                return root;
            root->parent = parent;
            if (root == target) {
                if (root->left == nullptr || root->right == nullptr) {
                    Node<T>* temp = root->left ? root->left : root->right;
                    delete root;
                    return temp;
                } else {
                    Node<T>* temp = minValueNode(root->right);
                    root->key = temp->key;
                    root->right = eraseNode(root->right, temp, root);
                }
            } else {
                if (target->key < root->key)
                    root->left = eraseNode(root->left, target, root);
                else
                    root->right = eraseNode(root->right, target, root);
            }
            if (root == nullptr)
                return root;
            root->height = std::max(height(root->left), height(root->right)) + 1;
            return balance(root);
        }


        //удаляет первый ключ
        Node<T>* remove(Node<T>* node, const T& key, Node<T>* parent) {
            if (node == nullptr) {
                return node;
            }
            node->parent = parent;
            if (key < node->key) {
                node->left = remove(node->left, key, node);
            } else if (key > node->key) {
                node->right = remove(node->right, key, node);
            } else {
                if (node->left == nullptr || node->right == nullptr) {
                    Node<T>* temp = node->left ? node->left : node->right;
                    if (temp == nullptr) {
                        delete node;
                        return nullptr;
                    } else {
                        temp->parent = parent;
                        delete node;
                        return temp;
                    }

                } else {
                    Node<T>* temp = minValueNode(node->right);
                    node->key = temp->key;
                    node->right = remove(node->right, temp->key, node);
                }
            }
            if (node == nullptr) {
                return node;
            }
            node->height = std::max(height(node->left), height(node->right)) + 1;
            return balance(node);
        }
        
        bool search(Node<T>* node, const T& key) {
            if (node == nullptr) {
                return false;
            }
            if (key == node->key) {
                return true;
            }
            if (key < node->key) {
                return search(node->left, key);
            }
            return search(node->right, key);
        }
};
