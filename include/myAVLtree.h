#pragma once

#include "commonHeader.h"
#include "myVector.h"
#include <exception>
#include <stdexcept>

template<typename T>
class AVLtree {
public:
    int operationsCount;
protected:
    struct node {
        Data<T> data;
        int32_t h;
        node* left;
        node* right;
        node(Data<T> d) : data(d), h(1), left(nullptr), right(nullptr) {}
    };
    node* root;
    node* leftRotation(node* n) {
        if (n == nullptr) throw std::runtime_error("Invalid left rotation argument: root nullptr");
        if (n->right == nullptr) throw std::runtime_error("Invalid left rotation argument: right nullptr");
        AVLtree::node* newn = n->right;
        n->right = newn->left;
        newn->left = n;

        n->h = 1 + ((n->right == nullptr) ? 0 : n->right->h); // right subtree is higher than left 
        newn->h = 1 + n->h;

        return newn;
    }
    node* rightRotation(node* n) {
        if (n == nullptr) throw std::runtime_error("Invalid right rotation argument: root nullptr");
        if (n->left == nullptr) throw std::runtime_error("Invalid right rotation argument: left nullptr");
        AVLtree::node* newn = n->left;
        n->left = newn->right;
        newn->right = n;

        n->h = 1 + ((n->left == nullptr) ? 0 : n->left->h);  // left subtree is higher than left 
        newn->h = 1 + n->h;

        return newn;
    }
    node* balance(node* n) {
        if (n == nullptr) return n;
        int32_t lefth = (n->left == nullptr) ? 0 : n->left->h;
        int32_t righth = (n->right == nullptr) ? 0 : n->right->h;
        n->h = 1 + ((lefth > righth) ? lefth : righth);

        if (lefth - righth == 2) {
            lefth = (n->left->left == nullptr) ? 0 : n->left->left->h; // n->left cannot be nullptr because if is 2 vertex higher than n->right
            righth = (n->left->right == nullptr) ? 0 : n->left->right->h;
            if (lefth - righth == -1) {
                n->left = leftRotation(n->left);
            }
            n = rightRotation(n);
        }
        else if (lefth - righth == -2) {
            lefth = (n->right->left == nullptr) ? 0 : n->right->left->h;
            righth = (n->right->right == nullptr) ? 0 : n->right->right->h;
            if (lefth - righth == 1) {
                n->right = rightRotation(n->right);
            }
            n = leftRotation(n);
        }

        return n;
    }
    node* recIns(node* n, const Data<T>& _data) {
        if (n == nullptr) {
            n = new node{ _data };
            return n;
        }
        else if (keycmpeq(n->data.key, _data.key)) {
            throw std::runtime_error("Cannot insert duplicates");
        }
        else if (keycmple(n->data.key, _data.key)) {
            n->right = recIns(n->right, _data);
        }
        else {
            n->left = recIns(n->left, _data);
        }

        return balance(n);
    }
    node* recDel(node* n, const myVector<char>& key) {
        node* tmp = nullptr;

        if (n == nullptr) return nullptr; // no element
        else if (keycmpeq(n->data.key, key)) { // found element
            if (n->left == nullptr || n->right == nullptr) { // has only 1 son
                tmp = (n->left == nullptr) ? n->right : n->left;
                delete n;
                return tmp;
            }
            tmp = n->right;
            while (tmp->left != nullptr) tmp = tmp->left; // the next element
            n->data = tmp->data; // swap data
            n->right = recDel(n->right, tmp->data.key);
        }
        else if (keycmple(n->data.key, key)) {
            n->right = recDel(n->right, key);
        }
        else {
            n->left = recDel(n->left, key);
        }

        return balance(n);
    }
public:
    AVLtree() : root(nullptr), operationsCount(0) {}
    Data<T> find(const myVector<char>& key) const {
        if (key.size() == 0) throw std::runtime_error("Invalid key");
        AVLtree::node* currentRoot = root;
        while (currentRoot != nullptr) {
            if (keycmpeq(currentRoot->data.key, key))
                return currentRoot->data;
            if (keycmple(currentRoot->data.key, key)) currentRoot = currentRoot->right;
            else currentRoot = currentRoot->left;
        }
        return Data<T>();
    }
    void ins(const Data<T>& _data) {
        if (_data.key.size() == 0) throw std::runtime_error("Invalid key");
        root = recIns(root, _data);
    }
    void del(const myVector<char>& key) {
        if (key.size() == 0) throw std::runtime_error("Invalid key");
        root = recDel(root, key);
    }
    ~AVLtree() {
        myQueue<node*> nodes;
        if (root != nullptr) nodes.push(root);
        while (!nodes.isEmpty()) {
            node* tmp = nodes.back();
            if (tmp->left != nullptr) nodes.push(tmp->left);
            if (tmp->right != nullptr) nodes.push(tmp->right);
            delete tmp;
        }
    }
};

class AVLtreeInterface : public AVLtree<polinom> {
public:
    void test_can_create_node();
    void test_can_right_rotation();
    void test_cant_right_rotation_nullptr_root();
    void test_cant_right_rotation_nullptr_left_son();
    bool test_right_rotation_only_two_elements_correct();
    bool test_right_rotation_correctly_interact_with_other_elements();
    void test_can_left_rotation();
    void test_cant_left_rotation_nullptr_root();
    void test_cant_left_rotation_nullptr_right_son();
    bool test_left_rotation_only_two_elements_correct();
    bool test_left_rotation_correctly_interact_with_other_elements();
    void test_can_balance();
    void test_can_balance_nullptr();
    bool test_correctly_balancing_one_small_left_disbalance();
    bool test_correctly_balancing_one_big_left_disbalance();
    bool test_correctly_balancing_one_small_right_disbalance();
    bool test_correctly_balancing_one_big_right_disbalance();
    void test_can_recursive_insert();
    void test_can_recursive_insert_nullptr();
    bool test_recursive_insert_nullptr_is_correct();
    bool test_recursive_insert_is_correct();
    void test_can_recursive_delete();
    void test_can_recursive_delete_nullptr();
    bool test_recursive_delete_nullptr_is_correct();
    bool test_recursive_delete_is_correct_0();
    bool test_recursive_delete_is_correct_1();
};