//
// Created by Dor Refaeli on 21/01/2020.
//

#include "HashPriorityQueueAStar.h"

template <typename P>
void HashPriorityQueueAStar<P>::insert(pair<P,double> element) {
    /*If exists already, must be removed first.
     *NOTE: if gets here, its derived from AStar's logic!*/
    if(my_set.count(element)) {
        my_set.erase(my_set.find(element));
    }
    this->my_set.insert(element);
    this->push(element);
}

template<typename P>
pair<P,double> HashPriorityQueueAStar<P>::topAndPop() {
    auto element = this->top();
    this->pop();
    this->my_set.erase(element);
    ++evaluated_nodes;
    return element;
}

template<typename P>
bool HashPriorityQueueAStar<P>::contains(pair<P,double> element) {
    return this->my_set.count(element);
}

template<typename P>
pair<P,double> HashPriorityQueueAStar<P>::find(pair<P,double> element) {
    return *(this->my_set.find(element));
}

