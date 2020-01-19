//
// Created by doref on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUE_H
#define ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUE_H

#include <queue>
#include <set>
#include "State.h"

using namespace std;

/**
 * A priority_queue wrapped by a class for the purpose of including a set
 * that will allow us to check if an element is in the the q in constant complexity.
 * The class inherits priority_queue.
 *
 * Important!!!
 *      The priority_queue comparator is the cost since the overridden operator in state are cost related.
 *      The set is manually set to compare via a position comparator
 */
template <typename E>
class HashPriorityQueue : public priority_queue<State<E>> {
private:
    set<State<E>> mySet;// POSITION_COMPARED
    int missed_inserts = 0;
public:
    HashPriorityQueue<E>() {
        this->mySet(State<E>(State<E>::positionComparator));
    }
    void insert(State<E> element);
    State<E> topAndPop();
    bool contains(State<E> element);
    State<E> find(State<E> element);
    void remove(State<E> element);
};


#endif //ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUE_H
