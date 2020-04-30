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
    Test_result testInsertFunction();
    Test_result test2();
    Test_result test3();
    Test_result testFindFunction();
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
    //assert(test2() == SUCCESS);
    //assert(test3() == SUCCESS);
    //assert(testFindFunction() == SUCCESS);
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
    return SUCCESS;
}

Test_result TestAVLTree::test2() {
    AVLTree<int,int> tree;
    for(int i=7;i>0;i--){
        tree.insert(i,i);
    }
    tree.printAVLTree(IN);
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
    AVLTree<int,int> tree;
    bool result = true;
    for(int i=25;i>0;i--){
        tree.insert(i,i);
    }
    int *a;
    for(int i=1; i<26; i++){
        a = tree.find(i);
        if(*a!=i) {
            return FAIL;
        }
    }
    return SUCCESS;

}


#endif //AVLTREE_TESTAVLTREE_H
