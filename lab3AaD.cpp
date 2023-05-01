#include <iostream>
#include"complexInt.h"

enum Color { RED, BLACK };

class Node {
public:
    Complex data;
    Color color;
    Node* parent;
    Node* left;
    Node* right;
    int size;

    Node(Complex d, Color c, Node* p, Node* l, Node* r, int s)
        : data(d), color(c), parent(p), left(l), right(r), size(s) {};
};

class OrderStatisticTree {
public:
    OrderStatisticTree() : root(nullptr) {};

    void Insert(Complex data) {
        Node* x = root;
        Node* y = nullptr;
        while (x != nullptr) {
            y = x;
            x->size++;
            if (data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        Node* z = new Node(data, RED, y, nullptr, nullptr, 1);
        if (y == nullptr)
            root = z;
        else if (data < y->data)
            y->left = z;
        else
            y->right = z;

        FixTreeAfterInsert(z);
    }

    Complex OrderStatistic(int k) {
        Node* x = root;
        while (x != nullptr) {
            int r = x->left ? x->left->size : 0;
            if (k == r + 1)
                return x->data;
            else if (k <= r)
                x = x->left;
            else {
                k = k - r - 1;
                x = x->right;
            }
        }
        return -1;
    }

private:
    Node* root;

    void FixTreeAfterInsert(Node* node) {
        while (node->parent != nullptr && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node* y = node->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    node->parent->color = BLACK;
                    y->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        RotateLeft(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    RotateRight(node->parent->parent);
                }
            }
            else {
                Node* y = node->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    node->parent->color = BLACK;
                    y->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        RotateRight(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    RotateLeft(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void RotateRight(Node* node) {
        Node* left_child = node->left;
        node->left = left_child->right;
        if (left_child->right != nullptr)
            left_child->right->parent = node;
        left_child->parent = node->parent;
        if (node->parent == nullptr)
            root = left_child;
        else if (node == node->parent->left)
            node->parent->left = left_child;
        else
            node->parent->right = left_child;
        left_child->right = node;
        node->parent = left_child;
        node->size = (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0) + 1;
        left_child->size = (left_child->left ? left_child->left->size : 0) + (left_child->right ? left_child->right->size : 0) + 1;
    }

    void RotateLeft(Node* node) {
        Node* right_child = node->right;
        node->right = right_child->left;
        if (right_child->left != nullptr)
            right_child->left->parent = node;
        right_child->parent = node->parent;
        if (node->parent == nullptr)
            root = right_child;
        else if (node == node->parent->left)
            node->parent->left = right_child;
        else
            node->parent->right = right_child;
        right_child->left = node;
        node->parent = right_child;
        node->size = (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0) + 1;
        right_child->size = (right_child->left ? right_child->left->size : 0) + (right_child->right ? right_child->right->size : 0) + 1;
    }
};

    int main() {
        setlocale(LC_ALL, "ukrainian");
        OrderStatisticTree tree;
        tree.Insert(Complex(120,15));
        tree.Insert(Complex(35,12));
        tree.Insert(Complex(1,5));
        tree.Insert(Complex(62,34));

        std::cout << "Елемент з 1 статистикою " << tree.OrderStatistic(1).getString() << std::endl;
        std::cout << "Елемент з 2 статистикою " << tree.OrderStatistic(2).getString() << std::endl;
        std::cout << "Елемент з 3 статистикою " << tree.OrderStatistic(3).getString() << std::endl;
        std::cout << "Елемент з 4 статистикою " << tree.OrderStatistic(4).getString() << std::endl;
       
    }
