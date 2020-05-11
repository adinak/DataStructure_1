//
// Created by Adina Katz on 28/04/2020.
//

#ifndef LINKEDLIST_LIST_H
#define LINKEDLIST_LIST_H

#include "listNode.h"
#include <ostream>

#define EMPTY 0

typedef enum {LIST_SUCCESS, LIST_IS_EMPTY, ELEMENT_EXISTS,
              ELEMENT_DOES_NOT_EXIST} ListResult;
typedef enum {LIST_FRONT, LIST_BACK} ListDirection;

template<typename T>
class List {
private:
    int length;
    ListNode<T>* head;
    ListNode<T>* tail;
    ListNode<T>* current;

    void increaseLength();
    void decreaseLength();

    void setHead(ListNode<T>* newHead);
    void setTail(ListNode<T>* newTail);

    ListResult findNode(ListNode<T>* node);

public:
    List();
    ~List();

    bool isEmpty() const;

    T getHeadData() const;
    T getTailData() const;
    T getCurrentData() const;
    int getLength() const;
    ListNode<T>* getHead() const;
    ListNode<T>* getTail() const;
    ListNode<T>* getCurrent() const;

    T getNextData();
    T getPrevData();
    void restartCurrent(ListDirection direction);

    void pushFirst(T data);
    void pushLast(T data);

    ListResult popNode(ListNode<T>* node);
    T popFirst();
    T popLast();
    void clearList();


    class Iterator{ //todo: adina
    private:
        ListNode<T>* data;
    public:
        Iterator(ListNode<T>* ptr = nullptr);
        ~Iterator() = default;

        Iterator operator=(ListNode<T>* node);
        Iterator operator=(Iterator new_itr);
        Iterator& operator++();
        ListNode<T>* operator*();
        bool operator==(Iterator itr);
    };
    Iterator begin();
    Iterator end();

    template<typename R>
    friend std::ostream& operator<<(std::ostream& os, const List<R>& list);

    friend class TestListNode; //TODO: debug
};

/**===========================================================================
 *                          Implementations
 ===========================================================================**/
/**================================ PRIVATE ================================**/
template<typename T>
void List<T>::increaseLength() {
    this->length++;
}

template<typename T>
void List<T>::decreaseLength() {
    this->length--;
}

template<typename T>
void List<T>::setHead(ListNode<T>* newHead) {
    this->head = newHead;
}

template<typename T>
void List<T>::setTail(ListNode<T>* newTail) {
    this->tail = newTail;
}

template<typename T>
ListResult List<T>::findNode(ListNode<T>* node) {
    if(this->isEmpty()) {
        return LIST_IS_EMPTY;
    }
    for( auto myCurrent = this->getHead(); myCurrent->getNext() != nullptr;
        myCurrent = myCurrent->getNext()) {
        if(current == node) {
            return ELEMENT_EXISTS;
        }
    }
    return ELEMENT_DOES_NOT_EXIST;
}

/**================================ PUBLIC ================================**/
template<typename T>
bool List<T>::isEmpty() const {
    return this->getLength() == EMPTY;
}

/** PUSH **/
template<typename T>
void List<T>::pushFirst(T data) {
    auto* newNode = new ListNode<T>(data);
    newNode->attachNode(nullptr, this->head);
    this->setHead(newNode);
    if(this->isEmpty()) {
        this->setTail(newNode);
    }
    this->increaseLength();
}

template<typename T>
void List<T>::pushLast(T data) {
    auto* newNode = new ListNode<T>(data);
    newNode->attachNode(this->tail, nullptr);
    this->setTail(newNode);
    if(this->isEmpty()) {
        this->setHead(newNode);
    }
    this->increaseLength();
}

/** GET **/
template<typename T>
T List<T>::getHeadData() const {
    if(this->isEmpty()) {
        T dummy = T();
        return dummy;
    }
    return this->head->getData();
}

template<typename T>
T List<T>::getTailData() const {
    if(this->isEmpty()) {
        T dummy = T();
        return dummy;
    }
    return this->tail->getData();
}

template<typename T>
T List<T>::getCurrentData() const {
    if(this->current == nullptr) {
        T dummy = T();
        return dummy;
    }
    return this->current->getData();
}

template<typename T>
T List<T>::getNextData() {
    if(this->current == nullptr) {
        this->restartCurrent(LIST_FRONT);
    }
    T data = this->current->getData();
    ListNode<T>* next = this->current->getNext();
    this->current = next;
    return data;
}

template<typename T>
T List<T>::getPrevData() {
    if(this->current == nullptr) {
        this->restartCurrent(LIST_BACK);
    }
    T data = this->current->getData;
    ListNode<T>* prev = this->current->getPrev();
    this->current = prev;
    return data;
}

template<typename T>
void List<T>::restartCurrent(ListDirection direction) {
    if(direction == LIST_FRONT) {
        this->current = this->getHead();
    } else if(direction == LIST_BACK){
        this->current = this->getTail();
    }
}

template<typename T>
int List<T>::getLength() const {
    return this->length;
}

template<typename T>
ListNode<T> *List<T>::getHead() const {
    return this->head;
}

template<typename T>
ListNode<T> *List<T>::getTail() const {
    return this->tail;
}

template<typename T>
ListNode<T> *List<T>::getCurrent() const {
    return this->current;
}

/** POP **/
template<typename T>
ListResult List<T>::popNode(ListNode<T>* node) {
    if(this->isEmpty()) {
        return LIST_IS_EMPTY;
    }
    if(node == this->getHead()) {
        this->popFirst();
        return LIST_SUCCESS;
    } else if(node == this->getTail()) {
        this->popLast();
        return LIST_SUCCESS;
    }
    if(this->findNode(node) == ELEMENT_EXISTS) {
        node->removeNode();
        delete node;
        this->decreaseLength();
        return LIST_SUCCESS;
    }

    return ELEMENT_DOES_NOT_EXIST;
}

template<typename T>
T List<T>::popFirst() {
    ListNode<T>* first = this->head;
    this->setHead(first->getNext());
    first->removeNode();
    T data = first->getData();
    this->decreaseLength();
    delete first;
    return data;
}

template<typename T>
T List<T>::popLast() {
    ListNode<T>* last = this->tail;
    this->tail = last->getPrev();
    last->removeNode();
    T data = last->getData();
    this->decreaseLength();
    delete last;
    return data;
}

/** C'TOR**/
template<typename T>
List<T>::List() : length(0), head(nullptr), tail(nullptr), current(nullptr) {}

/** D'TOR **/
template<typename T>
void List<T>::clearList() {
    while (this->head != nullptr) {
        this->popFirst();
    }
}

template<typename T>
List<T>::~List() {
    if(this->length != EMPTY) {
        this->clearList();
    }
}

/** PRINT **/
template<typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &list) {
    for(auto node = list.getHead(); node != nullptr;
        node = node->getNext()) {
        os << node->getData() << " ";
    }
    return os;
}



/**================================ ITERATOR ================================**/
//todo: adina
template<typename T>
List<T>::Iterator::Iterator(ListNode<T> *ptr) : data(ptr) { }

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator=(ListNode<T> *node) {
    this->data = node;
    return *this;
}

template<typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++() {
    this->data = this->data->getNext();
    return *this;
}

template<typename T>
ListNode<T> *List<T>::Iterator::operator*() {
    return this->data;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator=(List::Iterator new_itr) {
    this->data = new_itr->data;
    return *this;
}

template<typename T>
bool List<T>::Iterator::operator==(Iterator itr) {
    return (this->data == itr.data);
}

template<typename T>
typename List<T>::Iterator List<T>::begin() {
    return this->head;
}

template<typename T>
typename List<T>::Iterator List<T>::end() {
    return nullptr;
}

#endif //LINKEDLIST_LIST_H
