//
// Created by Aviv9 on 27/04/2020.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include "TreeNode.h"

enum AVLTreeResult {AVL_SUCCESS, AVL_NULL_ARG, AVL_KEY_NOT_FOUND, AVL_KEY_ALREADY_EXISTS};
enum AVLTreeOrderType{PRE, IN, POST, REVERSE};

template<class K, class D>
class AVLTree{
private:
    int num_of_nodes;
    TreeNode<K,D>* root;
    TreeNode<K,D>* biggest_node;

    void rotateLL(TreeNode<K,D>* B);
    void rotateLR(TreeNode<K,D>* C);
    void rotateRR(TreeNode<K,D>* B);
    void rotateRL(TreeNode<K,D>* C);

public:
    AVLTree();
    ~AVLTree() = default;
    AVLTreeResult insert(K& key, D& data);
    AVLTreeResult remove(const K& key);
    D* find(K key);

    template<typename Function>
    void iterateOverTree(AVLTreeOrderType type, Function do_something);

    //TODO:delete when done testing
    friend class TestAVLTree;

};

template<class K, class D>
void AVLTree<K,D>::rotateLL(TreeNode<K, D>* B) {
    TreeNode<K,D>* A = B->getLeft();
    B->setLeft(A->getRight());
    A->setRight(B);
}

template<class K, class D>
void AVLTree<K,D>::rotateLR(TreeNode<K, D>* C) {
    TreeNode<K,D>* B = C->getLeft();
    TreeNode<K,D>* A = B->getRight();

    B->setRight(A->setLeft());
    A->setLeft(B);
    C->setLeft(A->getRight());
    A->setRight(C);
}

template<class K, class D>
void rotateRR(TreeNode<K,D>* B){
    TreeNode<K,D>* A = B->getRight();
    B->setRight(A->getLeft());
    A->setLeft(B);
}

template<class K, class D>
void AVLTree<K,D>::rotateRL(TreeNode<K, D>* C) {
    TreeNode<K,D>* B = C->getRight();
    TreeNode<K,D>* A = B->getLeft();

    B->setLeft(A->getRight());
    A->setRight(B);
    C->setRight(A->getLeft());
    A->setLeft(C);
}
template<class K, class D>
AVLTreeResult insert(K& key, D& data){
    TreeNode<K,D> new_node = new TreeNode<K,D>(key,data);
    TreeNode<K,D> curr = this->root;
    //TODO: create new fuc add_node(*root, *new_node)
    if(curr == nullprt){
        this->root = new_node;
        return AVL_SUCCESS;
    }
    while(curr!= nullprt){
        int curr_key = curr.getKey();
        if(curr_key==key)
             return AVL_KEY_ALREADY_EXISTS;
        if(key>curr_key){
            curr->hr++;
            if(curr->getRight() == nullprt){
                curr->setRight(new_node);
                break;
            }
            curr = curr.getRight();
            continue;
        }
        if(key<curr_key){
            curr->hl++;
            if(curr->getLeft() == nullprt){
                curr->setLeft(new_node);
                break;
            }
            curr = curr.getLeft();
            continue;
        }
    }

}

template<class K, class D>
template<typename Function>
void AVLTree<K,D>::iterateOverTree(AVLTreeOrderType type, Function do_something) {

}

#endif //AVLTREE_AVLTREE_H
