//
// Created by doref on 19/01/2020.
//

#include <stdio.h>
#include <algorithm>

#include "HashPriorityQueue.h"

template <typename E>
void HashPriorityQueue<E>::insert(E element) {
    if(this->mySet.count(element) > 0) {
        this->missed_inserts++;
    }
    this->mySet.insert(element);
    this->push(element);
}

template<typename E>
E HashPriorityQueue<E>::topAndPop() {
    E element = this->top();
    this->pop();
    this->mySet.erase(element);
    return element;
}

template<typename E>
bool HashPriorityQueue<E>::contains(E element) {
    return this->mySet.count(element);
}

template<typename E>
E HashPriorityQueue<E>::find(E element) {
    //if doesn't exist
    if (!mySet.count(element)) {
        return nullptr;
    }
    return *(this->mySet.find(element));
}

template<typename E>
void HashPriorityQueue<E>::remove(E element) {
    auto it = std::find(this->c.begin(), this->c.end(), element); //TODO imported std::find from algorithm instead of <bits/streambuf_iterator.h>, make sure it's right
    if (it != this->c.end()) {
        this->c.erase(it);
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
    }
    else {
        perror("Tried to delete an non-existing element from the HashPriorityQueue");
        exit(1);
    }
}

