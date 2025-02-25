#include <initializer_list>
#include <algorithm>

template <typename T>
struct Node {
    T key;
    Node* left;
    Node* right;
    int height;

    Node(const T& key) : key(key), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree {

    public:

        void insert(const T& key) {
            root = insert(root_, key);
        }
        void remove(const T& key){
            root = remove(root_, key);
        }
        bool contains(const T& key) {
            return search(root_, key);
        }

        //конструкторы, нужно дописать
        AVLTree(): root_(nullptr) {}
        AVLTree(std::initializer_list<T> const &items) {
            for (auto it = items.begin(); it != items.end(); ++it) {
                root_ = insert(root_, *it);
            }
        }
        AVLTree(const AVLTree &other) : root_(copyTree(other.root_)) {}

        ~AVLTree() {
            destroy(root_);            
        }

    private:
        Node<T>* root_;  


        Node<T>* copyTree(Node<T>* node) {
            if (!node) return nullptr;
            Node<T>* newNode = new Node<T>(node->key);
            newNode->left = copyTree(node->left);
            newNode->right = copyTree(node->right);
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
            y->left = x->right;
            x->right = y;

            y->height = std::max(height(y->left), height(y->right)) + 1;
            x->height = std::max(height(x->left), height(x->right)) + 1;
            return x;
        } 

        Node<T>* rotateLeft(Node<T>* y) {
            Node<T>* x = y->right;
            y->right = x->left;
            x->left = y;

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

        Node<T>* insert(Node<T>* node, const T& key) {
            if (node == nullptr) {
                return new Node<T>(key); 
            }
            if (key < node->key) {
                node->left = insert(node->left, key);
            } else {
                node->right = insert(node->right, key);
            }
            node->height = std::max(height(node->left), height(node->right)) + 1;
            return balance(node);
        } 

        Node<T>* remove(Node<T>* node, const T& key) {
            if (node == nullptr) {
                return node;
            }
            if (key < node->key) {
                node->left = remove(node->left, key);
            } else if (key > node->key) {
                node->right = remove(node->right, key);
            } else {
                if (node->left == nullptr || node->right == nullptr) {
                    Node<T>* temp = node->left ? node->left : node->right;
                    if (temp == nullptr) {
                        delete node;
                        node = nullptr;
                    } else {
                        Node<T>* oldNode = node;
                        node = temp;
                        delete oldNode;
                    }

                } else {
                    Node<T>* temp = minValueNode(node->right);
                    node->key = temp->key;
                    node->right = remove(node->right, temp->key);
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
