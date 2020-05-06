//
// Created by Aviv9 on 27/04/2020.
//

#ifndef AVLTREE_TREENODE_H
#define AVLTREE_TREENODE_H

#include <iostream>
using std::ostream;

template<class K, class D>
class TreeNode{
private:
    D data;
    K key;
    TreeNode* left;
    TreeNode* right;
    TreeNode* father;
    int hl;
    int hr;

    D& getData();
    K& getKey();
    int getHeight();
    int getBf();
    TreeNode* getRight();
    TreeNode* getLeft();
    TreeNode* getFather();
    void setRight(TreeNode<K,D>* next);
    void setLeft(TreeNode<K,D>* next);
    void setSon(TreeNode<K,D>* next);


//    template<class KEY,class DATA>
//    friend std::ostream& operator<<(std::ostream& os, const TreeNode<KEY,DATA> &node);
    template <class KEY,class DATA>
    friend class AVLTree;



//TODO:delete when done testing
    friend class TestAVLTree;

public:
    TreeNode() : key(), data(), right(nullptr), left(nullptr),
                                                    father(nullptr), hl(0), hr(0){};
    TreeNode(K key, D data) : key(key), data(data), right(nullptr), left(nullptr),
                                                    father(nullptr), hl(0), hr(0){};
    ~TreeNode() = default;

    void printNode();

};

template<class K, class D>
K& TreeNode<K,D>::getKey() {
    return this->key;
}

template<class K, class D>
D& TreeNode<K,D>::getData() {
    return this->data;
}
template<class K, class D>
int TreeNode<K,D>::getHeight() {
    return ((this->hl>this->hr) ? this->hl:this->hr)+1;
}

template<class K, class D>
TreeNode<K,D>* TreeNode<K,D>::getLeft() {
    return this->left;
}

template<class K, class D>
TreeNode<K,D>* TreeNode<K,D>::getRight() {
    return this->right;
}

template<class K, class D>
TreeNode<K,D>* TreeNode<K,D>::getFather() {
    return this->father;
}


template<class K, class D>
void TreeNode<K,D>::setLeft(TreeNode<K,D>* next){
    this->left = next;
    if(next == nullptr){
        this->hl = 0;
    }
    else {
        this->hl = next->getHeight();
        next->father = this;
    }
}

template<class K, class D>
void TreeNode<K,D>::setRight(TreeNode<K,D>* next){
    this->right = next;
    if(next == nullptr){
        this->hr = 0;
    }
    else {
        this->hr = next->getHeight();
        next->father = this;
    }
}


template<class K, class D>
void TreeNode<K,D>::printNode(){
    std::cout<<"("<<this->getKey()<<", "<<this->getData()<<")";
}

template<class K, class D>
int TreeNode<K, D>::getBf() {
    return (this->hl-this->hr);
}
//
//template<class KEY, class DATA>
//std::ostream &operator<<(ostream &os, const TreeNode<KEY,DATA> &node) {
//    os<<"("<<node.key<<", "<<node.data<<")";
//    return os;
//}

template<class K, class D>
void TreeNode<K, D>::setSon(TreeNode<K, D> *next) {
    if(next->key > this->key) {
        this->setRight(next);
    }
    else {
        this->setLeft(next);
    }
}


#endif //AVLTREE_TREENODE_H
