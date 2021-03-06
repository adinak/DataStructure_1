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
    ListNode() = default;

    /**
     * Creates a new list node with data
     * @param data
     */
    ListNode(T data);
    ~ListNode() = default;

    /**
     * @return the next node in the list, after current
     */
    ListNode* getNext() const;

    /**
     * @return the previous node in the list, before current
     */
    ListNode* getPrev() const;

    /**
     * @return the data of current node
     */
    T getData() const;

    /**
     * Insert current node between prev and next
     * @param prev
     * @param next
     */
    void attachNode(ListNode* prev ,ListNode* next);

    /**
     * Remove node from current position
     * Attach the nodes before and after current
     */
    void removeNode();
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

template<typename T>
void ListNode<T>::attachNode(ListNode *newPrev, ListNode *newNext) {
    this->setNext(newNext);
    this->setPrev(newPrev);

    if(newPrev != nullptr) {
        newPrev->setNext(this);
    }
    if(newNext != nullptr) {
        newNext->setPrev(this);
    }
}

template<typename T>
void ListNode<T>::removeNode() {
    ListNode<T>* myNext = this->getNext();
    ListNode<T>* myPrev = this->getPrev();
    if(myNext != nullptr) {
        myNext->setPrev(myPrev);
    }
    if(myPrev != nullptr) {
        myPrev->setNext(myNext);
    }
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

/** C'TOR && D'TOR **/
template<typename T>
ListNode<T>::ListNode(T data) : data(data), next(nullptr), prev(nullptr){}



#endif //LINKEDLIST_LISTNODE_H
