//
// Created by Adina Katz on 29/04/2020.
//

#ifndef LINKEDLIST_LISTNODE_H
#define LINKEDLIST_LISTNODE_H

#include <ostream>

template<typename T>
class ListNode {
private:
    T data;
    ListNode* next;
    ListNode* prev;

    void setNext(ListNode* newNext);
    void setPrev(ListNode* newPrev);
    void setData(T newData);

public:
    explicit ListNode(T data);
    ~ListNode() = default;

    ListNode* getNext() const;
    ListNode* getPrev() const;
    T getData() const;

    //TODO: do i need this?
    /*template<typename R>
    friend class List;*/

    friend std::ostream& operator<<(std::ostream& os, const ListNode<T>&);

    friend class TestListNode; //debug
};

/**===========================================================================
 *                          Implementations
 ===========================================================================**/

/** SET **/
template<typename T>
void ListNode<T>::setNext(ListNode *newNext) {
    this->next = newNext;
}

template<typename T>
void ListNode<T>::setPrev(ListNode *newPrev) {
    this->prev = newPrev;
}

template<typename T>
void ListNode<T>::setData(T newData) {
    this->data = newData;
}

/** GET **/
template<typename T>
ListNode<T>* ListNode<T>::getNext() const {
    return this->next;
}

template<typename T>
ListNode<T>* ListNode<T>::getPrev() const {
    return this->prev;
}

template<typename T>
T ListNode<T>::getData() const {
    return this->data;
}

/** C'TOR **/
template<typename T>
ListNode<T>::ListNode(T data) : data(data), next(nullptr), prev(nullptr){}

/** Print **/
//TODO: currently not working
template<typename T>
std::ostream &operator<<(std::ostream &os, const ListNode<T> &node) {
    os << node.data;
    return os;
}

#endif //LINKEDLIST_LISTNODE_H
