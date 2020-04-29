//
// Created by Adina Katz on 28/04/2020.
//

#ifndef LINKEDLIST_LIST_H
#define LINKEDLIST_LIST_H

#include "listNode.h"
#include <ostream>

template<typename T>
class List {
private:
    int length;
    ListNode<T> head;
    ListNode<T> tail;

    void updateLength();
    void setHead(ListNode<T> newHead);
    void setTail(ListNode<T> newTail);

public:
    List();
    ~List() = default;

    T getHead();
    T getTail();
    T getHeadData(); //TODO
    T getTailData(); //TODO

    void insertFirst(ListNode<T> node);
    void insertLast(ListNode<T> node);

    void removeNode(ListNode<T> node);
    void clearList();

    friend std::ostream& operator<<(std::ostream& os, const List& list);
};

/**===========================================================================
 *                          Implementations
 ===========================================================================**/
/** SET **/
template<typename T>
void List<T>::updateLength() {
    this->length++;
}

template<typename T>
void List<T>::setHead(ListNode<T> newHead) {
    this->head = newHead;
}

template<typename T>
void List<T>::setTail(ListNode<T> newTail) {
    this->tail = newTail;
}

/** GET **/
template<typename T> //TODO: what is the right return value?!
T List<T>::getHeadData() {
    return this->head.getData();
}

template<typename T> //TODO: what is the right return value?!
T List<T>::getTailData() {
    return this->tail.getData();
}

template<typename T>
T List<T>::getHead() {
    return this->head;
}

template<typename T>
T List<T>::getTail() {
    return this->tail;
}

/** DELETE **/
template<typename T>
void List<T>::removeNode(ListNode<T> node) {
    if(node->prev == nullptr) {
        node->next->prev = nullptr;
        this->setHead(node->next);
    } else if(node->next == nullptr) {
        node->prev->next = nullptr;
        this->setTail(node->prev);
    } else {
        node->prev->next = this->next;
        node->next->prev = this->prev;
    }
}

template<typename T> //TODO: do i need this????
void List<T>::clearList() {

}

/** C'TOR**/
template<typename T>
List<T>::List() : length(0) {}


#endif //LINKEDLIST_LIST_H
