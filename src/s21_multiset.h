#ifndef S21_CONTAINERS_MULTISET_H
#define S21_CONTAINERS_MULTISET_H


#include <initializer_list>
#include <algorithm>
#include <iterator>
#include <limits>

namespace s21 {

template <typename Key>
class AVLTree {
    public:
        using value_type = Key;
        using key_type = Key;
        using reference = value_type&;
        using const_reference = const value_type&;
        using size_type = size_t;
        struct Node {
            Key key;
            Node* left;
            Node* right;
            Node* parent;
            int height;

            Node(const Key& key, Node* parent = nullptr) : key(key), left(nullptr), right(nullptr), parent(parent), height(1) {}
        };

        class iterator {
            public:
                using value_type = AVLTree::value_type;
                using reference = AVLTree::reference;
                using pointer = Key*;
                using iterator_category = std::bidirectional_iterator_tag;
                using difference_type = std::ptrdiff_t;

                iterator() : node_(nullptr), tree_(nullptr) {}
                iterator(Node<value_type>* node, const AVLTree<value_type>* tree) : node_(node), tree_(tree) {}

                reference operator*() {
                    return node_->key;
                }
                pointer operator->() {
                    return &(node_->key);
                }

                iterator& operator++() {
                    if (node_ == nullptr)
                        return *this;
                    if (node_->right != nullptr) {
                        node_ = minimum(node_->right);
                    } else {
                        Node<value_type>* p = node_->parent;
                        while (p != nullptr and node_ == p->right) {
                            node_ = p;
                            p = p->parent;
                        }
                        node_ = p;
                    }
                    return *this;
                }


                iterator& operator--() {
                    if (node_ == nullptr) {
                        node_ = maximum(tree_->root_);
                    } else if (node_->left != nullptr) {
                        node_ = maximum(node_->left); 
                    } else {
                        Node<value_type>* p = node_->parent;
                        while (p != nullptr and node_ == p->left) {
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
                Node<value_type>* node_;
                const AVLTree<value_type>* tree_;
                friend class AVLTree<value_type>;

                Node<value_type>* minimum(Node<value_type>* node) const {
                    while (node and node->left != nullptr) 
                        node = node->left;
                    return node;
                }

                Node<value_type>* maximum(Node<value_type>* node) const {
                    while (node and node->right != nullptr)
                        node = node->right;
                    return node;
                }
        };


        class const_iterator {
            public:
                using value_type = AVLTree::value_type;
                using const_reference = AVLTree::const_reference;
                using pointer = const Key*;
                using iterator_category = std::bidirectional_iterator_tag;
                using difference_type = std::ptrdiff_t;

                const_iterator() : node_(nullptr), tree_(nullptr) {}
                const_iterator(Node<value_type>* node, const AVLTree<value_type>* tree) : node_(node), tree_(tree) {}
                const_iterator(const iterator& it) : node_(it.node_), tree_(it.tree_) {}

                const_reference operator*() const {
                    return node_->key;
                }
                pointer operator->() const {
                    return &(node_->key);
                }

                const_iterator& operator++() {
                    if (node_ == nullptr)
                        return *this;
                    if (node_->right != nullptr) {
                        node_ = minimum(node_->right);
                    } else {
                        Node<value_type>* p = node_->parent;
                        while (p != nullptr and node_ == p->right) {
                            node_ = p;
                            p = p->parent;
                        }
                        node_ = p;
                    }
                    return *this;
                }


                const_iterator& operator--() {
                    if (node_ == nullptr) {
                        node_ = maximum(tree_->root_);
                    } else if (node_->left != nullptr) {
                        node_ = maximum(node_->left); 
                    } else {
                        Node<value_type>* p = node_->parent;
                        while (p != nullptr and node_ == p->left) {
                            node_ = p;
                            p = p->parent;
                        }
                        node_ = p;
                    }
                    return *this;
                }

                bool operator==(const const_iterator & other) const {
                    return node_ == other.node_;
                }

                bool operator!=(const const_iterator & other) const {
                    return !(*this == other);
                }

            private:
                Node<value_type>* node_;
                const AVLTree<value_type>* tree_;
                friend class AVLTree<value_type>;

                Node<value_type>* minimum(Node<value_type>* node) const {
                    while (node and node->left != nullptr) 
                        node = node->left;
                    return node;
                }

                Node<value_type>* maximum(Node<value_type>* node) const {
                    while (node and node->right != nullptr)
                        node = node->right;
                    return node;
                }
        };

        //конструкторы
        AVLTree(): root_(nullptr) {}

        AVLTree(std::initializer_list<value_type> const &items) {
            for (auto it = items.begin(); it != items.end(); ++it) {
                insert(*it);
            }
        }

        AVLTree(const AVLTree &other) : root_(copyTree(other.root_, nullptr)) {}


        bool empty() const {
            return (root_ == nullptr);
        }

        size_type size() const { 
            size_type counter = 0;
            for (auto it = this->begin(); it != this->end(); ++it) {
                counter += 1;
            }
            return counter;
        }

        size_type max_size() const {
            return std::numeric_limits<std::size_t>::max() / sizeof(Node<value_type>) / 2;
        }

        void clear() {
            destroy(root_); 
            root_ = nullptr;
        }

        iterator insert(const Key& key) {
            Node<value_type>* insertedNode = nullptr;
            root_ = insert(root_, key, nullptr, &insertedNode);
            return iterator(insertedNode, this);
        }

        void remove(const Key& key){ //удаление первого элемента с заданным ключем
            root_ = remove(root_, key, nullptr);
        }

        void erase(iterator pos) { //удаление конкретного элемента
            if (pos == end())
                return;
            root_ = eraseNode(root_, pos.node_, nullptr);
        }

        void swap(AVLTree& other) {
            if (this == &other)
                return;
            Node<value_type>* temp = this->root_;
            this->root_ = other.root_;
            other.root_ = temp;
        }

        void merge(AVLTree &other) {
            if (this == &other)
                return; 
            mergeNodes(other.root_);
            other.root_ = nullptr;
        }

        size_type count(const Key& key) const {
            return count(root_, key);
        }

        bool contains(const Key& key) const {
            return search(root_, key).node_ != nullptr;
        }

        const_iterator find(const Key& key) const {
            return search(root_, key);
        }

        iterator find(const Key& key) {
            return search(root_, key);
        }

        const_iterator lower_bound(const Key& key) const {
            return search_lower_bound(root_, key);
        }

        iterator lower_bound(const Key& key) {
            return search_lower_bound(root_, key);
        }

        const_iterator upper_bound(const Key& key) const {
            return search_upper_bound(root_, key);
        }

        iterator upper_bound(const Key& key) {
            return search_upper_bound(root_, key);
        }

        std::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
            return std::pair<const_iterator, const_iterator>(search_lower_bound(root_, key), search_upper_bound(root_, key));
        }

        std::pair<iterator,iterator> equal_range(const Key& key) {
            return std::pair<iterator,iterator>(search_lower_bound(root_, key), search_upper_bound(root_, key));
        }

        const_iterator begin() const {
            return iterator(minValueNode(root_), this);
        }

        iterator begin() {
            return iterator(minValueNode(root_), this);
        }

        const_iterator end() const  {
            return iterator(nullptr, this);
        }

        iterator end() {
            return iterator(nullptr, this);
        }

        ~AVLTree() {
            destroy(root_);            
        }
    private:
        Node<value_type>* root_;  
        friend class iterator;

        Node<value_type>* copyTree(Node<value_type>* node, Node<value_type>* parent) {
            if (!node) 
                return nullptr;
            Node<value_type>* newNode = new Node<value_type>(node->key, parent);
            newNode->left = copyTree(node->left, newNode);
            newNode->right = copyTree(node->right, newNode);
            newNode->height = node->height;
            return newNode;
        }

        void destroy(Node<value_type>* node) {
            if (node) {
                destroy(node->left);
                destroy(node->right);
                delete node;
            }
        }

        int height(Node<value_type>* node) {
            return node ? node->height: 0;
        }
        
        int getBalance(Node<value_type>* node) {
            return node ? (height(node->left) - height(node->right)) : 0;
        }

        Node<value_type>* rotateRight(Node<value_type>* y) {
            Node<value_type>* x = y->left;
            Node<value_type>* T2 = x->right;
            
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

        Node<value_type>* rotateLeft(Node<value_type>* x) {
            Node<value_type>* y = x->right;
            Node<value_type>* T2 = y->left;

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

        Node<value_type>* minValueNode(Node<value_type> *node) {
            Node<value_type>* current = node;
            while (current and current->left != nullptr) {
                current = current->left;
            }
            return current; 
        }

        Node<value_type>* balance(Node<value_type>* node) {
            int balanceFactor = getBalance(node);
            // Left Left
            if (balanceFactor > 1 and getBalance(node->left) >= 0) {
                return rotateRight(node);
            }
            // Left Right
            if (balanceFactor > 1 and getBalance(node->left) < 0) {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            // Right Right
            if (balanceFactor < -1 and getBalance(node->right) <= 0) {
                return rotateLeft(node);
            }
            // Right Left
            if (balanceFactor < -1 and getBalance(node->right) > 0) {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            return node;
        }

        //копирующая вставка по ключю
        Node<value_type>* insert(Node<value_type>* node, const Key& key, Node<value_type>* parent, Node<value_type>** inserted_node) {
            if (node == nullptr) {
                *inserted_node = new Node<value_type>(key, parent);
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


        // Вспомогательный метод для вставки уже выделенного узла. 
        // Перед вставкой нужно обнулить левый и правый дочерние указатели узла.
        Node<value_type>* insertNode(Node<value_type>* curr, Node<value_type>* node, Node<value_type>* parent) {
            if (!curr) {
                node->parent = parent;
                node->left = node->right = nullptr;
                node->height = std::max(height(node->left), height(node->right)) + 1;
                return node;
            }
            if (node->key < curr->key)
                curr->left = insertNode(curr->left, node, curr);
            else
                curr->right = insertNode(curr->right, node, curr);
            curr->height = std::max(height(curr->left), height(curr->right)) + 1;
            return balance(curr);
        }

        void mergeNodes(Node<value_type>* node) {
            if (!node)
                return;
            mergeNodes(node->left);
            mergeNodes(node->right);
            // «Отрываем» данный узел от дерева-источника
            node->left = node->right = nullptr;
            node->parent = nullptr;
            // Вставляем узел в текущее дерево
            root_ = insertNode(root_, node, nullptr);
        }

        //удаляет по указателю
        Node<value_type>* eraseNode(Node<value_type>* root, Node<value_type>* target, Node<value_type>* parent) {
            if (root == nullptr)
                return root;
            root->parent = parent;
            if (root == target) {
                if (root->left == nullptr || root->right == nullptr) {
                    Node<value_type>* temp = root->left ? root->left : root->right;
                    delete root;
                    if (temp != nullptr) {
                        temp->parent = parent;
                    }
                    return temp;
                } else {
                    Node<value_type>* temp = minValueNode(root->right);
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
        Node<value_type>* remove(Node<value_type>* node, const Key& key, Node<value_type>* parent) {
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
                    Node<value_type>* temp = node->left ? node->left : node->right;
                    if (temp == nullptr) {
                        delete node;
                        return nullptr;
                    } else {
                        temp->parent = parent;
                        delete node;
                        return temp;
                    }

                } else {
                    Node<value_type>* temp = minValueNode(node->right);
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
        
        size_type count(Node<value_type>* node, const Key &key) const {
            if (!node)
                return 0;
            if (key < node->key)
                return count(node->left, key);
            else if (node->key < key)
                return count(node->right, key);
            else {
                // При равенстве ключей, согласно логике вставки,
                // дубликаты располагаются в правом поддереве.
                // Поэтому считаем текущий узел и ищем оставшиеся равные ключи только в правом поддереве.
                return 1 + count(node->right, key);
            }
        }

        iterator search(Node<value_type>* node, const Key& key) const {
            if (node == nullptr) {
                return iterator(node, this);
            }
            if (key == node->key) {
                return iterator(node, this);;
            }
            if (key < node->key) {
                return search(node->left, key);
            }
            return search(node->right, key);
        }

        iterator search_lower_bound(Node<value_type>* node, const Key& key) const {
            Node<value_type>* res = nullptr;
            while (node != nullptr) {
                if (!(node->key < key)) { //node->key >= key
                    res = node;
                    node = node->left;
                } else {
                    node = node->right;
                }
            }
            return iterator(res, this);
        }

        iterator search_upper_bound(Node<value_type>* node, const Key& key) const {
            Node<value_type>* res = nullptr;
            while (node != nullptr) {
                if (key < node->key) {
                    res = node;
                    node = node->left;
                } else {
                    node = node->right;
                }
            }
            return iterator(res, this);
        }
};

} // namespace s21

#endif