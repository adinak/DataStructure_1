//
// Created by Aviv9 on 27/04/2020.
//


//test push
#ifndef AVLTREE_TREENODE_H
#define AVLTREE_TREENODE_H

#include <iostream>
using std::ostream;

template<class K, class D>
class TreeNode{
private:
    //private variables for internal use
    D data;
    K key;
    TreeNode* left;
    TreeNode* right;
    //bidirectional tree
    TreeNode* father;
    //left subtree height
    int hl;
    //right subtree height
    int hr;

    //return reference to data attribute
    D& getData();
    //return reference to key attribute
    K& getKey();
    //compute the height of the node according to hl and hr
    int getHeight();
    //Balance factor for Avl tree, Bf = hl-hr
    int getBf();
    TreeNode* getRight();
    TreeNode* getLeft();
    TreeNode* getFather();
    void setRight(TreeNode<K,D>* next);
    void setLeft(TreeNode<K,D>* next);
    //set next as left/right son according to next key value
    void setSon(TreeNode<K,D>* next);

    template <class KEY,class DATA>
    friend class AVLTree;

public:
    /**
     * default TreeNode constructor, uses D and K default constructors
     */
    TreeNode() : data(), key(), left(nullptr), right(nullptr),
                                                father(nullptr), hl(0), hr(0){};
    /**
     * creating new Node with the given data and key parameters
     * @param key
     * @param data
     */
    TreeNode(K key, D data) :  data(data), key(key),left(nullptr),
                              right(nullptr), father(nullptr), hl(0), hr(0){};
    /**
     * no new memory is allocated so default destructor is fine
     */
    ~TreeNode() = default;

    /**
     * print node attributes, for debugging purposes
     */
    void printNode();

};

/** Getters **/

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
int TreeNode<K, D>::getBf() {
    return (this->hl-this->hr);
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

/** Setters **/

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
void TreeNode<K, D>::setSon(TreeNode<K, D> *next) {
    if(next->key > this->key) {
        this->setRight(next);
    }
    else {
        this->setLeft(next);
    }
}


/** Printnig Function **/

template<class K, class D>
void TreeNode<K,D>::printNode(){
    std::cout<<"("<<this->getKey()<<", "<<this->getData()<<")";
}



#endif //AVLTREE_TREENODE_H
