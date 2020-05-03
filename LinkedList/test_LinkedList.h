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

/*void TestListNode::test2() {
    //create list
    List<int> my_list;
    cout << "# Created empty list successfully #" << endl;

    //create nodes
    ListNode<int> node_1(1);
    ListNode<int> node_2(2);

    //test pushFirst
    my_list.pushFirst(&node_2);
    my_list.pushFirst(&node_1);
    cout << "# Pushed two nodes into the list successfully #" << endl;

    // test insert worked correctly
    cout << "head: " << my_list.getHeadData() << endl;
    cout << "tail: " << my_list.getTailData() << endl;

    // test << operator
    //cout << my_list;

    // create third node
    ListNode<int> node_3(3);

    // test pushLast
    my_list.pushLast(&node_3);
    cout << "# Pushed to end of list successfully #" << endl;

    // test all nodes are in list correctly
    cout << my_list.getHeadData() << endl;
    cout << my_list.head->next->getData() << endl;
    cout << my_list.getTailData() << endl;

    // test getLength() and popping a specific node
    cout << "list length: " << my_list.getLength() << endl;
    assert(my_list.popNode(&node_1) == LIST_SUCCESS);
    cout << "# Popped a specific node from the list successfully #" << endl;
    cout << "list length: " << my_list.getLength() << endl;

    // test all nodes are in list correctly
    cout << my_list.getHeadData() << endl;
    cout << my_list.head->next->getData() << endl;
    cout << my_list.getTailData() << endl;

    // test popping a node that doesn't exist in the list
    ListNode<int> node_10(10);
    assert(my_list.popNode(&node_10) == ELEMENT_DOES_NOT_EXIST);

    assert(my_list.popNode(&node_2) == LIST_SUCCESS);
    //cout << my_list;
    cout << "list length: " << my_list.getLength() << endl;
    assert(my_list.popNode(&node_3) == LIST_SUCCESS);
    //cout << my_list;
    cout << "list length: " << my_list.getLength() << endl;
    assert(my_list.popNode(&node_3) == LIST_IS_EMPTY);
}
*/

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
}

void TestListNode::test() {
    //test1();
    test3();
}

#endif //LINKEDLIST_TEST_LINKEDLIST_H
