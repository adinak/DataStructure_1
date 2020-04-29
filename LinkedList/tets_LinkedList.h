//
// Created by Adina Katz on 29/04/2020.
//

#ifndef LINKEDLIST_TETS_LINKEDLIST_H
#define LINKEDLIST_TETS_LINKEDLIST_H

#include <iostream>
#include "listNode.h"
#include <vector>
using namespace std;

typedef enum {SUCCESS, FAIL} Test_Result;

class TestListNode {
private:
    Test_Result test1();
    Test_Result test2();
public:
    TestListNode() = default;
    ~TestListNode() = default;

    Test_Result test();

};

Test_Result TestListNode::test1() {
    ListNode<int> node_1(1);
    ListNode<int> node_2(2);

    node_1.setNext(&node_2);
    node_2.setPrev(&node_1);

    cout << "data 1 is: " << node_2.prev->data << endl;
    cout << "data 2 is: " << node_1.next->data << endl;

    node_1.setData(4);

    cout << "data 1 is: " << node_1.getData() << endl;

    ListNode<int> node_3(3);
    node_3.setNext(&node_2);
    node_3.setPrev(&node_1);
    node_1.setNext(&node_3);
    node_2.setPrev(&node_3);

    //cout << node_1 << endl;
    //cout << node_2 << endl;
    //cout << node_3 << endl;
    cout << "data 3 is: " << node_1.next->data << endl;

    node_1.removeNode();
    assert(node_3.prev == nullptr);

    return SUCCESS;
}

Test_Result TestListNode::test() {
    test1();
    return SUCCESS;
}




#endif //LINKEDLIST_TETS_LINKEDLIST_H
