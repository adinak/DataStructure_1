//
// Created by Aviv9 on 27/04/2020.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

//TODO: replace with Adina's List
#include <list>
using std::list;

#include "TreeNode.h"


typedef enum {AVL_SUCCESS, AVL_KEY_ALREADY_EXISTS, AVL_KEY_NOT_EXISTS,
                                        BALANCED, NOT_BALANCED} AVLTreeResult;
typedef enum {PRE, IN, POST, REVERSE} AVLTreeOrderType;

template<class K, class D>
class AVLTree{
private:
    int num_of_nodes;
    TreeNode<K,D>* root;
    TreeNode<K,D>* biggest_node;

    AVLTreeResult rotateLL(TreeNode<K,D>* B);
    AVLTreeResult rotateLR(TreeNode<K,D>* C);
    AVLTreeResult rotateRR(TreeNode<K,D>* B);
    AVLTreeResult rotateRL(TreeNode<K,D>* C);

    AVLTreeResult addNewNode(TreeNode<K,D>* new_node);
    AVLTreeResult balanceNode(TreeNode<K,D>* curr);
//TODO: replace with Adina's List
    AVLTreeResult getPreOrder(TreeNode<K,D>* root_node, std::list<D>* ordered_list);
    AVLTreeResult getInOrder(TreeNode<K, D> *root_node, list<D> *ordered_list);
    AVLTreeResult getPostOrder(TreeNode<K, D> *root_node, list<D> *ordered_list);
    AVLTreeResult getReverseOrder(TreeNode<K, D> *root_node, list<D> *ordered_list, int &n);

    AVLTreeResult swapNodes(TreeNode<K,D>* a, TreeNode<K,D>* b);
    TreeNode<K, D> * deleteNode(TreeNode<K, D> *node_to_delete);
    AVLTreeResult deleteNodeWithTwoChildren(TreeNode<K,D>* node_to_delete);
    TreeNode<K,D>* findNode(const K& key);

    //TODO:delete when done testing
    friend class TestAVLTree;

public:
    AVLTree():root(nullptr), biggest_node(nullptr), num_of_nodes(0) {};
    ~AVLTree() = default;
    int getSize();
    AVLTreeResult insert(K& key, D& data);
    AVLTreeResult remove(const K& key);
    D* find(const K& key);
    void printAVLTree(AVLTreeOrderType type);
    //TODO: replace with Adina's List
    AVLTreeResult getTreeToList(AVLTreeOrderType type, list<D> *ordered_list);
    AVLTreeResult getNLargestNodes(list<D> *ordered_list, int &n);
};

template<class K, class D>
int AVLTree<K, D>::getSize() {
    return this->num_of_nodes;
}

template<class K, class D>
AVLTreeResult AVLTree<K,D>::rotateLL(TreeNode<K, D>* B) {
    TreeNode<K,D>* A = B->getLeft();
    TreeNode<K,D>* father = B->getFather();

    B->setLeft(A->getRight());
    A->setRight(B);
    if(father == nullptr){
        A->father = nullptr;
        this->root = A;
    }
    else if(A->getKey()>father->getKey()){
        father->setRight(A);
    }
    else if(A->getKey()<father->getKey()){
        father->setLeft(A);
    }
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K,D>::rotateLR(TreeNode<K, D>* C) {
    TreeNode<K,D>* B = C->getLeft();
    TreeNode<K,D>* A = B->getRight();
    TreeNode<K,D>* father = C->getFather();

    B->setRight(A->getLeft());
    A->setLeft(B);
    C->setLeft(A->getRight());
    A->setRight(C);
    if(father == nullptr){
        A->father = nullptr;
        this->root = A;
    }
    else if(A->getKey()>father->getKey()){
        father->setRight(A);
    }
    else if(A->getKey()<father->getKey()){
        father->setLeft(A);
    }
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::rotateRR(TreeNode<K, D> *B) {
    TreeNode<K,D>* A = B->getRight();
    TreeNode<K,D>* father = B->getFather();

    B->setRight(A->getLeft());
    A->setLeft(B);
    if(father == nullptr){
        A->father = nullptr;
        this->root = A;
    }
    else if(A->getKey()>father->getKey()){
        father->setRight(A);
    }
    else if(A->getKey()<father->getKey()){
        father->setLeft(A);
    }
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K,D>::rotateRL(TreeNode<K, D>* C) {
    TreeNode<K,D>* B = C->getRight();
    TreeNode<K,D>* A = B->getLeft();
    TreeNode<K,D>* father = C->getFather();

    B->setLeft(A->getRight());
    A->setRight(B);
    C->setRight(A->getLeft());
    A->setLeft(C);
    if(father == nullptr){
        A->father = nullptr;
        this->root = A;
    }
    else if(A->getKey()>father->getKey()){
        father->setRight(A);
    }
    else if(A->getKey()<father->getKey()){
        father->setLeft(A);
    }
    return AVL_SUCCESS;
}


template<class K, class D>
AVLTreeResult AVLTree<K, D>::addNewNode(TreeNode<K,D>* new_node) {
    K key = new_node->getKey();
    D data = new_node->getData();
    TreeNode<K,D>* curr = this->root;
    bool new_biggest_node = true;
    if(curr == nullptr){
        this->root = new_node;
        this->biggest_node = new_node;
        return AVL_SUCCESS;
    }
    while(curr!= nullptr){
        int curr_key = curr->getKey();
        if(curr_key==key) {
            delete new_node;
            return AVL_KEY_ALREADY_EXISTS;
        }
        else if(key>curr_key){
            if(curr->getRight() == nullptr){
                curr->setRight(new_node);
                if(new_biggest_node){
                    this->biggest_node = new_node;
                }
                break;
            }
            curr = curr->getRight();
        }
        else if(key<curr_key){
            new_biggest_node = false;
            if(curr->getLeft() == nullptr){
                curr->setLeft(new_node);
                break;
            }
            curr = curr->getLeft();
        }
    }
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::balanceNode(TreeNode<K, D> *curr) {
    if(curr->getBf()==2){
        if(curr->getLeft()->getBf() >= 0){
            if(rotateLL(curr) == AVL_SUCCESS) return BALANCED;
            //TODO: delete before submission
            else exit(1);
        }
        if(curr->getLeft()->getBf() == -1){
            if(rotateLR(curr) == AVL_SUCCESS) return BALANCED;
            //TODO: delete before submission
            else exit(1);
        }
        //TODO: delete before submission
        else {
            std::cout << "wrong BF in " << *curr << std::endl;
            exit(1);
        }
    }
    if(curr->getBf()==-2){
        if(curr->getRight()->getBf() <= 0){
            if(rotateRR(curr) == AVL_SUCCESS) return BALANCED;
            //TODO: delete before submission
            else exit(0);
        }
        if(curr->getRight()->getBf() == 1){
            if(rotateRL(curr) == AVL_SUCCESS) return BALANCED;
            //TODO: delete before submission
            else exit(0);
        }
        //TODO: delete before submission
        else {
            std::cout << "wrong BF in " << *curr << std::endl;
            exit(0);
        }
    }
    return NOT_BALANCED;
}

template<class K, class D>
AVLTreeResult AVLTree<K,D>::insert(K& key, D& data){
    TreeNode<K,D>* new_node = new TreeNode<K,D>(key,data);
    AVLTreeResult add_result = addNewNode(new_node);
    if(add_result != AVL_SUCCESS){
        return add_result;
    }
    this->num_of_nodes++;
    AVLTreeResult balance_result = NOT_BALANCED;
    TreeNode<K,D>* curr = new_node;
    int son_key = curr->getKey();

    for(curr = new_node->getFather(); curr != nullptr ;curr=curr->getFather()){
        if(son_key>curr->getKey()){
            curr->hr = curr->getRight()->getHeight();
        }
        else if(son_key<curr->getKey()){
            curr->hl = curr->getLeft()->getHeight();
        }
        if(balance_result == NOT_BALANCED) {
            balance_result = balanceNode(curr);
        }
        son_key = curr->getKey();
    }
    return AVL_SUCCESS;
}



template<class K, class D>
AVLTreeResult AVLTree<K, D>::getPreOrder(TreeNode<K, D> *root_node, list<D> *ordered_list) {
    if(root_node == nullptr) return AVL_SUCCESS;
    ordered_list->push_back(root_node->getData());
    getPreOrder(root_node->getLeft(),ordered_list);
    getPreOrder(root_node->getRight(),ordered_list);
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::getInOrder(TreeNode<K, D> *root_node, list<D> *ordered_list) {
    if(root_node == nullptr) return AVL_SUCCESS;
    getInOrder(root_node->getLeft(),ordered_list);
    ordered_list->push_back(root_node->getData());
    getInOrder(root_node->getRight(),ordered_list);
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::getPostOrder(TreeNode<K, D> *root_node, list<D> *ordered_list) {
    if(root_node == nullptr) return AVL_SUCCESS;
    getPostOrder(root_node->getLeft(),ordered_list);
    getPostOrder(root_node->getRight(),ordered_list);
    ordered_list->push_back(root_node->getData());
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::getReverseOrder(TreeNode<K, D> *root_node, list<D> *ordered_list, int &n) {
    //TODO: delete before submition
    if(n < 0) {
        std::cout<<"getReverse, num of node < 0";
        exit(1);
    }
    if(root_node == nullptr || n == 0) return AVL_SUCCESS;
    getReverseOrder(root_node->getRight(), ordered_list, n);
    if(n == 0) return AVL_SUCCESS;
    ordered_list->push_back(root_node->getData());
    n--;
    getReverseOrder(root_node->getLeft(), ordered_list, n);
}



template<class K, class D>
void AVLTree<K, D>::printAVLTree(AVLTreeOrderType type) {
    list<D> ordered_list;
    getTreeToList(type, &ordered_list);
    for(auto data : ordered_list){
        std::cout<<data<<", ";
    }
    std::cout<<std::endl;
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::getNLargestNodes(list<D> *ordered_list, int &n) {
    TreeNode<K,D>* curr = biggest_node;
    if(curr == nullptr) return AVL_SUCCESS;

    getReverseOrder(curr, ordered_list, n);
    curr = curr->getFather();
    while(curr!= nullptr && n > 0){
        ordered_list->push_back(curr->getData());
        n--;
        getReverseOrder(curr->getLeft(), ordered_list, n);
        curr = curr->getFather();
    }
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::getTreeToList(AVLTreeOrderType type, list<D> *ordered_list) {
    switch(type){
        case PRE:
            getPreOrder(this->root, ordered_list);
            break;
        case IN:
            getInOrder(this->root, ordered_list);
            break;
        case POST:
            getPostOrder(this->root, ordered_list);
            break;
        case REVERSE:
            getReverseOrder(this->root, ordered_list, num_of_nodes);
    }
    return AVL_SUCCESS;
}

template<class K, class D>
TreeNode<K, D>* AVLTree<K, D>::findNode(const K &key) {
    TreeNode<K,D>* curr = root;
    while(curr != nullptr){
        K curr_key = curr->getKey();
        if(curr_key == key){
            return curr;
        }
        else if(key<curr_key){
            curr = curr->getLeft();
        }
        else if(key>curr_key){
            curr = curr->getRight();
        }
    }
    return nullptr;
}

template<class K, class D>
D* AVLTree<K, D>::find(const K &key) {
    TreeNode<K,D>* node_to_find = findNode(key);
    return &node_to_find->getData();
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::swapNodes(TreeNode<K, D>* a, TreeNode<K, D>* b) {
    if(a->getHeight()>b->getHeight()){
        TreeNode<K,D>* tmp = b;
        b=a;
        a=tmp;
    }
    //tmp = b
    TreeNode<K,D>* b_father = b->getFather();
    TreeNode<K,D>* b_left = b->getLeft();
    TreeNode<K,D>* b_right = b->getRight();
    K b_key = b->getKey();
    if(this->biggest_node->getKey() == b_key){
        this->biggest_node = a;
    }
    if(this->biggest_node->getKey() == a->getKey()){
        this->biggest_node = b;
    }
    //b = a
    b->setLeft(a->getLeft());
    b->setRight(a->getRight());
    a->getFather()->setSon(b);
    //a = tmp
    a->setLeft(b_left);
    a->setRight(b_right);
    if(b_father != nullptr) {
        b_father->setSon(a);
    }
    else{
        this->root = a;
    }
    return AVL_SUCCESS;
}

template<class K, class D>
TreeNode<K, D> * AVLTree<K, D>::deleteNode(TreeNode<K, D> *node_to_delete) {
    TreeNode<K,D> *dead;
    TreeNode<K,D>* father = node_to_delete->getFather();
    bool biggest = (this->biggest_node->getKey() == node_to_delete->getKey());
    if (node_to_delete->getLeft() != nullptr && node_to_delete->getRight() == nullptr) {
        dead = node_to_delete;
        if(father == nullptr){
            this->root = node_to_delete->getLeft();
        }
        else{
            father->setSon(node_to_delete->getLeft());
        }
        if(biggest){
            this->biggest_node = this->biggest_node->getLeft();
            while(this->biggest_node->getRight() != nullptr) {
                this->biggest_node = this->biggest_node->getRight();
            }
        }
        delete dead;
        return node_to_delete;
    }
    else if (node_to_delete->getLeft() == nullptr && node_to_delete->getRight() != nullptr) {
        dead = node_to_delete;
        node_to_delete = node_to_delete->getRight();
        if(father == nullptr){
            this->root = node_to_delete->getLeft();
        }
        else{
            father->setSon(node_to_delete->getLeft());
        }
        delete dead;
        return node_to_delete;
    }
    else if (node_to_delete->getLeft() == nullptr && node_to_delete->getRight() == nullptr) {
        dead = node_to_delete;
        if(father == nullptr){
            this->root = nullptr;
        }
        else if(node_to_delete->key > father->getKey()){
            father->setRight(nullptr);
        }
        else{
            father->setLeft(nullptr);
        }
        if(biggest){
            this->biggest_node = father;
        }
        delete dead;
        return father;
    }
    else {
        deleteNodeWithTwoChildren(node_to_delete);
    }
    return nullptr;
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::deleteNodeWithTwoChildren(TreeNode<K, D> *node_to_delete) {
    TreeNode<K,D>* curr = node_to_delete;
    curr = curr->getRight();
    while(curr->getLeft()!=nullptr){
        curr = curr->getLeft();
    }
    swapNodes(curr, node_to_delete);
    deleteNode(curr);
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::remove(const K &key) {
    TreeNode<K,D>* node_to_delete = findNode(key);
    if(node_to_delete== nullptr){
        return AVL_KEY_NOT_EXISTS;
    }
    TreeNode<K,D>* curr = deleteNode(node_to_delete);
    this->num_of_nodes--;
    int son_key;
    if(curr != nullptr){
        son_key= curr->getKey();
    }
    for(; curr != nullptr ;curr=curr->getFather()){
        if(son_key>curr->getKey()){
            curr->hr = curr->getRight()->getHeight();
        }
        else if(son_key<curr->getKey()){
            curr->hl = curr->getLeft()->getHeight();
        }
        balanceNode(curr);
        son_key = curr->getKey();
    }
}


#endif //AVLTREE_AVLTREE_H