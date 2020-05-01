//
// Created by Aviv9 on 28/04/2020.
//

#ifndef AVLTREE_TESTAVLTREE_H
#define AVLTREE_TESTAVLTREE_H

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include "AVLTree.h"
#include "vector"
#include "set"
#include "list"
using namespace std;

typedef enum {SUCCESS, FAIL} Test_result;

#define TEST(i) testi()

void print(list<int> a){
    cout<<"(";
    for(int x : a){
        cout<<x<<", ";
    }
    cout<<")"<<endl;
}

class TestAVLTree {
private:
    AVLTree<int,int>* createRandomTree(int num_of_numbers, int random_range, list<int>* in_order_list);
    AVLTree<int,int>* createRandomTree(int num_of_numbers, int random_range);
    Test_result testInsertFunction();
    Test_result testFindFunction();
    Test_result testRemoveFunction();
    Test_result test3();
public:
    TestAVLTree(){
        srand (time(nullptr));
    };
    ~TestAVLTree() = default;
    Test_result test();

};

Test_result TestAVLTree::test() {
    assert(testInsertFunction() == SUCCESS);
    cout<<"testInsertFunction - SUCCESS"<<endl;
    //assert(test3() == SUCCESS);
    assert(testFindFunction() == SUCCESS);
    cout<<"testFindFunction - SUCCESS"<<endl;
    assert(testRemoveFunction() == SUCCESS);
    cout<<"testInsertFunction - SUCCESS"<<endl;
    return SUCCESS;
}

Test_result TestAVLTree::testInsertFunction() {
    AVLTree<int,int> tree;
    list<int> tester;
    list<int> result;
    int num_of_numbers = 10000;
    int random_range = 1000000;
    for(int i=0;i<num_of_numbers; i++){
        int num = (rand()%random_range);
        tester.push_back(num);
        result.push_back(num);
    }
    result.sort();
    result.unique();
//  cout<<"old_tester = ";
//  print(tester);
//  cout<<"result = ";
//  print(result);
    int i=0;
    while(!tester.empty()) {
        tree.insert(tester.back(), tester.back());
        tester.pop_back();
        i++;
    }
    tester.clear();
    tree.getTreeToList(IN, &tester);
    if(tester != result){
        cout<<"tree IN order = ";
        tree.printAVLTree(IN);
        cout<<"new_tester = ";
        print(tester);
        return FAIL;
    }
    assert(tree.checkSum(tree.root));
    return SUCCESS;
}

Test_result TestAVLTree::testRemoveFunction() {
    list<int> in_order_list;
    AVLTree<int,int>* tree = createRandomTree(100,1000, &in_order_list);
    list<int> result;
    tree->getTreeToList(IN, &result);
    assert(result == in_order_list);
    while(!in_order_list.empty()){
        int a = in_order_list.front();
        tree->remove(a);
        assert(tree->checkSum(tree->root));
        in_order_list.pop_front();
        result.clear();
        tree->getTreeToList(IN, &result);
        assert(result == in_order_list);
    }
    return SUCCESS;
}

Test_result TestAVLTree::test3() {
    AVLTree<int,int> tree;
    for(int i=7;i>0;i--){
        tree.insert(i,i);
    }
    list<int> ordered_list;
    int n = 4;
    tree.getNLargestNodes(&ordered_list, n);
    for(auto n : ordered_list){
        cout<<n<<" ,";
    }
    return SUCCESS;
}

Test_result TestAVLTree::testFindFunction() {
    Test_result result = SUCCESS;
    list<int> in_order_list;
    AVLTree<int,int>* tree = createRandomTree(100, 1000, &in_order_list);
    int a;
    while(!in_order_list.empty()){
        a = in_order_list.front();
        in_order_list.pop_front();
        int b = *tree->find(a);
        if(a != b){
          result = FAIL;
          break;
        }
    }
    delete tree;
    return result;

}

AVLTree<int, int> *TestAVLTree::createRandomTree(int num_of_numbers, int random_range, list<int>* in_order_list) {
    AVLTree<int,int>* tree = new AVLTree<int,int>();
    list<int> tester;
    for(int i=0;i<num_of_numbers; i++){
        int num = (rand()%random_range);
        tester.push_back(num);
        in_order_list->push_back(num);
    }
    in_order_list->sort();
    in_order_list->unique();
    int i=0;
    while(!tester.empty()) {
        tree->insert(tester.back(), tester.back());
        tester.pop_back();
        i++;
    }
    return tree;
}

AVLTree<int, int> *TestAVLTree::createRandomTree(int num_of_numbers, int random_range) {
    AVLTree<int,int>* tree = new AVLTree<int,int>();
    list<int> tester;
    for(int i=0;i<num_of_numbers; i++){
        int num = (rand()%random_range);
        tester.push_back(num);
    }
    while(!tester.empty()) {
        tree->insert(tester.back(), tester.back());
        tester.pop_back();
    }
    return tree;
}


#endif //AVLTREE_TESTAVLTREE_H
