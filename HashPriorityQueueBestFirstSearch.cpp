//
// Created by Dor Refaeli on 19/01/2020.
//

#include <stdio.h>
#include <algorithm>
#include <iostream>

#include "HashPriorityQueueBestFirstSearch.h"

template <typename E>
void HashPriorityQueueBestFirstSearch<E>::insert(E element) {
    if(this->mySet.count(element) > 0) {
        this->missed_inserts++;
    }
    this->mySet.insert(element);
    this->push(element);
    if(this->size() != this->mySet.size()) {
        clog << "Error! priority queue and his set aren't the size!" << endl;
    }
}

template<typename E>
E HashPriorityQueueBestFirstSearch<E>::topAndPop() {
    E element = this->top();
    this->pop();
    this->mySet.erase(element);
    return element;
}

template<typename E>
bool HashPriorityQueueBestFirstSearch<E>::contains(E element) {
    return this->mySet.count(element);
}

template<typename E>
E HashPriorityQueueBestFirstSearch<E>::find(E element) {
    //if doesn't exist
    if (!mySet.count(element)) {
        return nullptr;
    }
    return *(this->mySet.find(element));
}

template<typename E>
void HashPriorityQueueBestFirstSearch<E>::remove(E element) {
    auto it = std::find(this->c.begin(), this->c.end(), element);
    if (it != this->c.end()) {
        this->c.erase(it);
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
        this->mySet.erase(this->mySet.find(element));
    } else {
        perror("Tried to delete an non-existing element from the HashPriorityQueueBestFirstSearch");
        exit(1);
    }
}

