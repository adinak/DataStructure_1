//
// Created by Aviv9 on 27/04/2020.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

//TODO: replace with Adina's List
//using std::list;

#include "TreeNode.h"
#include "list.h"


typedef enum {AVL_SUCCESS, AVL_KEY_ALREADY_EXISTS, AVL_KEY_NOT_EXISTS,
                                        BALANCED, NOT_BALANCED} AVLTreeResult;
typedef enum {PRE, IN, POST} AVLTreeOrderType;

/**
 * Creating and operating AVL Tree, as learnt at the lectures.
 * Storing, accessing at removing data at binary-search tree, while O(h)=log(n)
 * when "h" stands for tree's depth and "n" stands for nodes stored at the tree.
 * @tparam K Datatype of node KEY
 * @tparam D Datatype of node DATA
 */
template<class K, class D>
class AVLTree{
private:
    //Number of nodes in the tree
    int num_of_nodes;
    TreeNode<K,D>* root;
    //Pointer to the node with the smallest_node Key
    TreeNode<K,D>* smallest_node;

    //Rotating function for inserting or deleting nodes
    AVLTreeResult rotateLL(TreeNode<K,D>* B);
    AVLTreeResult rotateLR(TreeNode<K,D>* C);
    AVLTreeResult rotateRR(TreeNode<K,D>* B);
    AVLTreeResult rotateRL(TreeNode<K,D>* C);

    //Add new_node to the tree
    AVLTreeResult addNewNode(TreeNode<K,D>* new_node);
    //Balance single tree node
    AVLTreeResult balanceNode(TreeNode<K,D>* curr);

    //Transferring the tree nodes data to lists according to specific order
    AVLTreeResult getPreOrder(TreeNode<K,D>* root_node, List<D> *ordered_list);
    AVLTreeResult getPreOrder(TreeNode<K,D>* root_node, List<D> *ordered_list,
                                                                        int& n);

    AVLTreeResult getInOrder(TreeNode<K, D> *root_node, List<D> *ordered_list);
    AVLTreeResult getInOrder(TreeNode<K, D> *root_node, List<D> *ordered_list,
                                                                        int& n);

    AVLTreeResult getPostOrder(TreeNode<K, D> *root_node,
                                                        List<D> *ordered_list);
    AVLTreeResult getPostOrder(TreeNode<K, D> *root_node,
                                                List<D> *ordered_list, int& n);

    //Swap two nodes position, used for deleting nodes
    AVLTreeResult swapNodes(TreeNode<K,D>* a, TreeNode<K,D>* b);
    //Deleting node from the tree
    TreeNode<K, D> * deleteNode(TreeNode<K, D> *node_to_delete);
    //Deleting node with two children required special handling therefore
    // it has special function
    TreeNode<K, D> * deleteNodeWithTwoChildren(TreeNode<K,D>* node_to_delete);

    //Find node in the tree with a specific key
    TreeNode<K,D>* findNode(const K& key);

    //Delete all the nodes from the tree
    void clearTree(TreeNode<K, D> *root_node);

    /*Iterate over the tree nodes in in-order and using doSomthing function on
     *the nodes data, doSomthing need to have exactly 3 parameters:
     *
     */
    template<typename Function, typename S>
    AVLTreeResult iterateAndDoInOrder(TreeNode<K, D> *node, Function
        doSomething, List<S>* lst ,int &n);

public:
    // C'tors and D'tors
    AVLTree();
    ~AVLTree();

    //return the num of nodes in the tree
    int getSize();

    //Insert & Remove
    /**
     * Adds new item to the tree, while keeping it balanced
     * @param key Identifier of new item
     * @param data Data of new item
     * @return AVL_SUCCESS / AVL_KEY_ALREADY_EXISTS
     */
    AVLTreeResult insert(K& key, D& data);

    /**
     * Removes an item from the tree, while keeping it balanced
     * @param key Identifier of removed item
     * @return AVL_SUCCESS / AVL_KEY_NOT_EXISTS
     */
    AVLTreeResult remove(const K& key);

    /**
     * Searches after a specific item, identifies by key, and returns a pointer
     * to its data
     * @param key Identifier for desired item
     * @return pointer to the data associated with the specific key / nullptr if
     * the specific key do not exists
     */
    D* find(const K& key);

    /**
     * Prints (to std::cout) the content of the tree, by using selected search
     * method
     * @param type Search method (PRE, IN, POST)
     */
    void printAVLTree(AVLTreeOrderType type);

    // Data Accessing
    /**
     * Puts data stored at the tree to a given List<D>, using given search order
     * @param Order type for the search (PRE, IN, POST)
     * @param data_list List<D> to store search results at
     * @param optional param that indicate the number of nodes to store in the
     *        list
     */
    AVLTreeResult getTreeToList(AVLTreeOrderType type, List<D> *ordered_list);
    AVLTreeResult getTreeToList(AVLTreeOrderType type, List<D> *ordered_list,
                                                                        int& n);

    /**
     * Iterate over n of the tree nodes in in-order and use doSomething function
     * on each nodes data.
     * to use the function the user need to create a class with () operator
     * overloaded with spesific params
     * @param doSomething(D data, int &n, List<S>* lst)
     *        @param data is the nodes data to operate on
     *        @param n uses to count the number of action (the user can increase
     *               decrease n in order to count actions)
     *        @param lst - list to store inner structs, can be nullptr if not
     *                     used
     * @param number of nodes/ actions to made
     * @return AVL_SUCCESS
     */
    template<typename Function, typename S>
    AVLTreeResult doSomethingInOrder(Function doSomething, int &n, List<S>*lst);

    /**
     * Delete all the nodes from the tree and set Private variable to nullptr
     */
    void clear();
};

/* ###################################################
 *          Implementation - Public Functions
 * ###################################################
 */

/* ----------------------------------
 *         C'tors and D'tors
 * ----------------------------------
 */

template<class K, class D>
AVLTree<K, D>::AVLTree():num_of_nodes(0), root(nullptr), smallest_node(nullptr){}

template<class K, class D>
AVLTree<K, D>::~AVLTree() {
    clearTree(this->root);
    num_of_nodes = 0;
    this->root = nullptr;
    this->smallest_node = nullptr;
}

/* ----------------------------------
 *         Get Size
 * ----------------------------------
 */

template<class K, class D>
int AVLTree<K, D>::getSize() {
    return this->num_of_nodes;
}

/* ----------------------------------
 *         Insert & Remove
 * ----------------------------------
 */

template<class K, class D>
AVLTreeResult AVLTree<K,D>::insert(K& key, D& data){
    TreeNode<K,D>* new_node = new TreeNode<K,D>(key,data);
    AVLTreeResult add_result = addNewNode(new_node);//Adds the node to the tree
    if(add_result != AVL_SUCCESS){//Something went wrong
        delete new_node;
        return add_result;
    }
    this->num_of_nodes++;
    AVLTreeResult balance_result = NOT_BALANCED;
    TreeNode<K,D>* curr = new_node;
    int son_key = curr->getKey();
    //Checking the BF of each node in the route to the root, updating heights
    for(curr = new_node->getFather(); curr != nullptr ;curr=curr->getFather()){
        //checking in which direction we went up
        if(son_key>curr->getKey()){
            curr->hr = curr->getRight()->getHeight();
        }
        else if(son_key<curr->getKey()){
            curr->hl = curr->getLeft()->getHeight();
        }
        //after one rotation the tree is balanced
        if(balance_result == NOT_BALANCED) {
            balance_result = balanceNode(curr);
        }
        son_key = curr->getKey();
    }
    return AVL_SUCCESS;
}

/**Rotation Functios**/

template<class K, class D>
AVLTreeResult AVLTree<K,D>::rotateLL(TreeNode<K, D>* B) {
    //B is the unbalanced node with BF>1
    TreeNode<K,D>* A = B->getLeft();
    TreeNode<K,D>* father = B->getFather();

    B->setLeft(A->getRight());
    A->setRight(B);
    if(father == nullptr){//that means B is the root
        A->father = nullptr;
        this->root = A;
    }
    else {
        father->setSon(A);
    }
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K,D>::rotateLR(TreeNode<K, D>* C) {
    //C is the unbalanced node with BF>1
    TreeNode<K,D>* B = C->getLeft();
    //B has BF=1 therefore he has a right son
    TreeNode<K,D>* A = B->getRight();
    TreeNode<K,D>* father = C->getFather();

    B->setRight(A->getLeft());
    A->setLeft(B);
    C->setLeft(A->getRight());
    A->setRight(C);
    if(father == nullptr){//that means C is the root
        A->father = nullptr;
        this->root = A;
    }
    else {
        father->setSon(A);
    }
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::rotateRR(TreeNode<K, D> *B) {
    //B is the unbalanced node with BF<-1
    TreeNode<K,D>* A = B->getRight();
    TreeNode<K,D>* father = B->getFather();

    B->setRight(A->getLeft());
    A->setLeft(B);
    if(father == nullptr){//that means B is the root
        A->father = nullptr;
        this->root = A;
    }
    else {
        father->setSon(A);
    }
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K,D>::rotateRL(TreeNode<K, D>* C) {
    //C is the unbalanced node with BF<-1
    TreeNode<K,D>* B = C->getRight();
    //B has BF=1 therefore he has a right son
    TreeNode<K,D>* A = B->getLeft();
    TreeNode<K,D>* father = C->getFather();

    B->setLeft(A->getRight());
    A->setRight(B);
    C->setRight(A->getLeft());
    A->setLeft(C);
    if(father == nullptr){//that means C is the root
        A->father = nullptr;
        this->root = A;
    }
    else {
        father->setSon(A);
    }
    return AVL_SUCCESS;
}

/**Adding Node Function**/

template<class K, class D>
AVLTreeResult AVLTree<K, D>::addNewNode(TreeNode<K,D>* new_node) {
    K key = new_node->getKey();
    TreeNode<K,D>* curr = this->root;
    bool new_smallest_node = true;
    if(curr == nullptr){
        this->root = new_node;
        this->smallest_node = new_node;
        return AVL_SUCCESS;
    }
    while(curr!= nullptr){
        int curr_key = curr->getKey();
        if(curr_key==key) {
            return AVL_KEY_ALREADY_EXISTS;
        }
        else if(key>curr_key){
            if(curr->getRight() == nullptr){
                curr->setRight(new_node);
                if(new_smallest_node){
                    this->smallest_node = new_node;
                }
                break;
            }
            curr = curr->getRight();
        }
        else if(key<curr_key){
            new_smallest_node = false;
            if(curr->getLeft() == nullptr){
                curr->setLeft(new_node);
                break;
            }
            curr = curr->getLeft();
        }
    }
    return AVL_SUCCESS;
}

/** Balance Node Function **/

template<class K, class D>
AVLTreeResult AVLTree<K, D>::balanceNode(TreeNode<K, D> *curr) {
    if(curr->getBf()==2){
        if(curr->getLeft()->getBf() >= 0){
            if(rotateLL(curr) == AVL_SUCCESS) return BALANCED;
        }
        if(curr->getLeft()->getBf() == -1){
            if(rotateLR(curr) == AVL_SUCCESS) return BALANCED;
        }
    }
    if(curr->getBf()==-2){
        if(curr->getRight()->getBf() <= 0){
            if(rotateRR(curr) == AVL_SUCCESS) return BALANCED;
        }
        if(curr->getRight()->getBf() == 1){
            if(rotateRL(curr) == AVL_SUCCESS) return BALANCED;
        }
    }
    return NOT_BALANCED;
}

/** Remove main Function **/

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
    return AVL_SUCCESS;
}

/** Swap Two Nodes **/
template<class K, class D>
AVLTreeResult AVLTree<K, D>::swapNodes(TreeNode<K, D>* a, TreeNode<K, D>* b) {
    if(b->getHeight()>a->getHeight()){
        TreeNode<K,D>* tmp = a;
        a=b;
        b=tmp;
    }
    TreeNode<K,D>* a_father = a->getFather();
    TreeNode<K,D>* b_father = b->getFather();

    if (b_father == a) {   // In case a is parent of b
        if (a->getLeft()->key == b->key) {
            b->setLeft(a);
            a->setLeft(nullptr);
            b->setRight(a->getRight());
            a->setRight(nullptr);
        } else { // Right son
            b->setLeft(a->getLeft());
            a->setLeft(nullptr);
            TreeNode<K,D>* tn_new_right = b->getRight();
            b->setRight(a);
            a->setRight(tn_new_right);
        }

        // Deal with fathers
        if (a == this->root) {
            this->root = b;
            b->father = nullptr;
        }
        else {
            if (a_father->getLeft() != nullptr &&
                                        a_father->getLeft()->key == a->key) {
                a_father->setLeft(b);
            }
            else{
                a_father->setRight(b);
            }
        }
    }
    else { // At least 1 node between a, b
        b->setLeft(a->getLeft());
        a->setLeft(nullptr);
        TreeNode<K,D>* tn_new_right = b->getRight();
        b->setRight(a->getRight());
        a->setRight(tn_new_right);

        if (a == this->root) {
            this->root = b;
            b->father = nullptr;
        }
        else {
            if (a_father->getLeft() != nullptr &&
                                        a_father->getLeft()->key == a->key) {
                a_father->setLeft(b);
            }
            else {
                a_father->setRight(b);
            }
        }
        if (b_father->getLeft() != nullptr &&
                                        b_father->getLeft()->key == b->key) {
            b_father->setLeft(a);
        }
        else {
            b_father->setRight(a);
        }
    }
    return AVL_SUCCESS;
}

/** Delete Node **/
template<class K, class D>
TreeNode<K, D> * AVLTree<K, D>::deleteNode(TreeNode<K, D> *node_to_delete) {
    TreeNode<K,D>* dead;
    TreeNode<K,D>* father = node_to_delete->getFather();
    bool biggest = (this->smallest_node->getKey() == node_to_delete->getKey());
    if (node_to_delete->getLeft() != nullptr &&
                                        node_to_delete->getRight() == nullptr) {
        dead = node_to_delete;
        if(father == nullptr){
            this->root = node_to_delete->getLeft();
            this->root->father = nullptr;
        }
        else{
            father->setSon(node_to_delete->getLeft());
        }
        if(biggest){
            this->smallest_node = this->smallest_node->getLeft();
            while(this->smallest_node->getRight() != nullptr) {
                this->smallest_node = this->smallest_node->getRight();
            }
        }
        delete dead;
        return father;
    }
    else if (node_to_delete->getLeft() == nullptr &&
                                        node_to_delete->getRight() != nullptr) {
        dead = node_to_delete;
        if(father == nullptr){
            this->root = node_to_delete->getRight();
            this->root->father = nullptr;
        }
        else{
            father->setSon(node_to_delete->getRight());
        }
        delete dead;
        return father;
    }
    else if (node_to_delete->getLeft() == nullptr &&
                                        node_to_delete->getRight() == nullptr) {
        dead = node_to_delete;
        if(father == nullptr){
            this->root = nullptr;
        }
        else if(father->getRight() &&
                        (node_to_delete->key == father->getRight()->getKey())){
            father->setRight(nullptr);
        }
        else{
            father->setLeft(nullptr);
        }
        if(biggest){
            this->smallest_node = father;
        }
        delete dead;
        return father;
    }
    else {
        return deleteNodeWithTwoChildren(node_to_delete);
    }
}

/** Delete Node With Two Children **/
template<class K, class D>
TreeNode<K, D> * AVLTree<K, D>::deleteNodeWithTwoChildren(
                                            TreeNode<K, D> *node_to_delete) {
    TreeNode<K,D>* curr = node_to_delete;
    curr = curr->getRight();
    while(curr->getLeft()!=nullptr){
        curr = curr->getLeft();
    }
    swapNodes(curr, node_to_delete);
    return deleteNode(node_to_delete);
}





/** Print Function **/
template<class K, class D>
void AVLTree<K, D>::printAVLTree(AVLTreeOrderType type) {
    List<D> ordered_list;
    getTreeToList(type, &ordered_list);
    std::cout<<ordered_list<<std::endl;
}

/* ----------------------------------
 *        Getters To List
 * ----------------------------------
 */
template<class K, class D>
AVLTreeResult AVLTree<K, D>::getTreeToList(AVLTreeOrderType type, List<D> *ordered_list) {
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
    }
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::getTreeToList(AVLTreeOrderType type, List<D> *ordered_list, int &n) {
    switch(type){
        case PRE:
            getPreOrder(this->root, ordered_list, n);
            break;
        case IN:
            getInOrder(this->root, ordered_list, n);
            break;
        case POST:
            getPostOrder(this->root, ordered_list, n);
            break;
    }
    return AVL_SUCCESS;
}

/** Recursive Order Functions **/

template<class K, class D>
AVLTreeResult AVLTree<K, D>::getPreOrder(TreeNode<K, D> *root_node,
                                                    List <D> *ordered_list) {
    if(root_node == nullptr) return AVL_SUCCESS;
    ordered_list->pushLast(root_node->getData());
    getPreOrder(root_node->getLeft(),ordered_list);
    getPreOrder(root_node->getRight(),ordered_list);
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::getInOrder(TreeNode<K, D> *root_node,
                                                    List<D> *ordered_list) {
    if(root_node == nullptr) return AVL_SUCCESS;
    getInOrder(root_node->getLeft(),ordered_list);
    ordered_list->pushLast(root_node->getData());
    getInOrder(root_node->getRight(),ordered_list);
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::getPostOrder(TreeNode<K, D> *root_node,
                                                    List<D> *ordered_list) {
    if(root_node == nullptr) return AVL_SUCCESS;
    getPostOrder(root_node->getLeft(),ordered_list);
    getPostOrder(root_node->getRight(),ordered_list);
    ordered_list->pushLast(root_node->getData());
    return AVL_SUCCESS;
}


template<class K, class D>
AVLTreeResult AVLTree<K, D>::getPreOrder(TreeNode<K, D> *root_node, List<D> *ordered_list, int &n) {
    if(root_node == nullptr || n == 0) return AVL_SUCCESS;
    ordered_list->pushLast(root_node->getData());
    n--;
    getPreOrder(root_node->getLeft(), ordered_list, n);
    getPreOrder(root_node->getRight(), ordered_list, n);
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::getInOrder(TreeNode<K, D> *root_node, List<D> *ordered_list, int &n) {
    if(root_node == nullptr || n == 0) return AVL_SUCCESS;
    getInOrder(root_node->getLeft(), ordered_list, n);
    if(n == 0) return AVL_SUCCESS;
    ordered_list->pushLast(root_node->getData());
    n--;
    getInOrder(root_node->getRight(), ordered_list, n);
    return AVL_SUCCESS;
}

template<class K, class D>
AVLTreeResult AVLTree<K, D>::getPostOrder(TreeNode<K, D> *root_node, List<D> *ordered_list, int &n) {
    if(root_node == nullptr || n == 0) return AVL_SUCCESS;
    getPostOrder(root_node->getLeft(), ordered_list, n);
    getPostOrder(root_node->getRight(), ordered_list, n);
    if(n == 0) return AVL_SUCCESS;
    ordered_list->pushLast(root_node->getData());
    n--;
    return AVL_SUCCESS;
}

/* ----------------------------------
 *               Find
 * ----------------------------------
 */

template<class K, class D>
D* AVLTree<K, D>::find(const K &key) {
    TreeNode<K,D>* node_to_find = findNode(key);
    if(node_to_find == nullptr){
        return nullptr;
    }
    return &node_to_find->getData();
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

/* ----------------------------------
 *              Clear
 * ----------------------------------
 */

template<class K, class D>
void AVLTree<K, D>::clear() {
    clearTree(this->root);
    num_of_nodes = 0;
    this->root = nullptr;
    this->smallest_node = nullptr;
    return;
}

template<class K, class D>
void AVLTree<K, D>::clearTree(TreeNode<K, D> *root_node) {
    if(root_node == nullptr) return;
    clearTree(root_node->getLeft());
    clearTree(root_node->getRight());
    delete root_node;
}

/* ----------------------------------
 *  User-Custom  Iterate Functions
 * ----------------------------------
 */

template<class K, class D>
template<typename Function, typename S>
AVLTreeResult AVLTree<K, D>::doSomethingInOrder(Function doSomething, int &n,
 List<S>* lst ) {
    return iterateAndDoInOrder(this->root, doSomething, lst, n);
}

template<class K, class D>
template<typename Function, typename S>
AVLTreeResult AVLTree<K, D>::iterateAndDoInOrder(TreeNode<K, D> *node,
                                Function doSomething, List<S>* lst, int &n) {
    if(node == nullptr || n == 0) return AVL_SUCCESS;
    iterateAndDoInOrder(node->getLeft(), doSomething, lst, n);
    if(n == 0) return AVL_SUCCESS;
    doSomething(node->getData(), n, lst);
    iterateAndDoInOrder(node->getRight(), doSomething, lst, n);
    return AVL_SUCCESS;
}


#endif //AVLTREE_AVLTREE_H
