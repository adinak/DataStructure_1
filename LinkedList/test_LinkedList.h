//
// Created by Adina Katz on 29/04/2020.
//

#ifndef LINKEDLIST_TEST_LINKEDLIST_H
#define LINKEDLIST_TEST_LINKEDLIST_H

#include <iostream>
#include "listNode.h"
#include "list.h"
#include <cassert>

using namespace std;

class TestListNode {
private:
    void test1();
    void test2();
    void test3();

public:
    TestListNode() = default;
    ~TestListNode() = default;

    void test();

};

void TestListNode::test1() {
    ListNode<int> node_1(1);
    ListNode<int> node_2(2);

    node_1.setNext(&node_2);
    node_2.setPrev(&node_1);

    cout << "data 1 is: " << node_2.prev->getData() << endl;
    cout << "data 2 is: " << node_1.next->getData() << endl;

    node_1.setData(4);

    cout << "data 1 is: " << node_1.getData() << endl;

    ListNode<int> node_3(3);
    node_3.setNext(&node_2);
    node_3.setPrev(&node_1);
    node_1.setNext(&node_3);
    node_2.setPrev(&node_3);

    cout << "data 3 is: " << node_1.next->getData() << endl;

    //assert(node_3.prev == nullptr);

}

void TestListNode::test2() {
    List<int> my_list;
    cout << "# CREATED EMPTY LIST #" << endl;

    for (int i = 100; i > 0; --i) {
        my_list.pushFirst(i);
    }

    cout << my_list << endl;
    my_list.restartCurrent();
    bool flag = true;
    while(my_list.getCurrent() != nullptr) {
        cout << "current is: " << my_list.getNextData() << endl;
        if(my_list.getCurrentData() == 10 && flag) {
            my_list.restartCurrent();
            flag = false;
        }
    }
    cout << "current is: " << my_list.getNextData() << endl;

    my_list.clearList();
    cout << "list length: " << my_list.getLength() << endl;
    cout << "head: " << my_list.getHeadData() << endl;
}


void TestListNode::test3() {
    List<int> my_list;
    cout << "# CREATED EMPTY LIST #" << endl;
    my_list.pushFirst(1);
    my_list.pushFirst(2);
    my_list.pushLast(3);
    my_list.pushLast(4);
    cout << "# ADD 4 NODES TO THE LIST #" << endl;
    cout << my_list << endl;
    cout << "POPPED: " << my_list.popFirst() << endl;
    cout << my_list << endl;
    cout << "POPPED: " << my_list.popLast() << endl;
    cout << my_list << endl;
    cout << "Head data: " << my_list.getHeadData() << endl;
    cout << "Tail data: " << my_list.getTailData() << endl;
    my_list.clearList();
    cout << "list length: " << my_list.getLength() << endl;
}

void TestListNode::test() {
    test2();
    test3();
}

#endif //LINKEDLIST_TEST_LINKEDLIST_H
