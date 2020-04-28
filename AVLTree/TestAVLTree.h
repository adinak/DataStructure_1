//
// Created by Aviv9 on 28/04/2020.
//

#ifndef AVLTREE_TESTAVLTREE_H
#define AVLTREE_TESTAVLTREE_H

#include <iostream>
#include "TreeNode.h"
#include "AVLTree.h"
#include "vector"
using namespace std;

typedef enum {SUCCESS, FAIL} Test_result;


class TestAVLTree {
private:
    Test_result test1();
    Test_result test2();
public:
    TestAVLTree() = default;
    ~TestAVLTree() = default;
    Test_result test();

};


Test_result TestAVLTree::test1() {
    vector<TreeNode<int,char>*> nodes;
    TreeNode<int,char> A(2,'A');
    nodes.push_back(&A);
    TreeNode<int,char> AL(3,'L');
    nodes.push_back(&AL);
    TreeNode<int,char> AR(4,'R');
    nodes.push_back(&AR);
    TreeNode<int,char> B(1,'B');
    nodes.push_back(&B);
    TreeNode<int,char> BL(5,'L');
    nodes.push_back(&BL);
    TreeNode<int,char> BR(6,'R');
    nodes.push_back(&BR);
    TreeNode<int,char> C(0,'C');
    nodes.push_back(&C);
    TreeNode<int,char> CL(7,'L');
    nodes.push_back(&CL);
    TreeNode<int,char> CR(8,'R');
    nodes.push_back(&CL);
    TreeNode<int,char> N(3,'n');
    nodes.push_back(&N);

    AL.setLeft(&N);
    A.setLeft(&AL);
    A.setRight(&AR);
    B.setRight(&A);
    B.setLeft(&BL);
    C.setLeft(&B);
    C.setRight(&CR);

    for(auto node : nodes){
        cout<<"(key:"<<node->getKey()<<", "<<"data:"<<node->getData()<<", "<<"hl:"<<node->hl<<", hr:"<<node->hr<<", BF:"<<node->getBf()<<endl;
    }


    return FAIL;
}

Test_result TestAVLTree::test() {

    return SUCCESS;
}


#endif //AVLTREE_TESTAVLTREE_H
