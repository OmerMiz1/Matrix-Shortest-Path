//
// Created by doref on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEBESTFIRSTSEARCH_H
#define ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEBESTFIRSTSEARCH_H

#include <queue>
#include <set>
#include "State.h"

using namespace std;

template <typename E>
class positionComparator {
    bool operator()(const E &first, const E &second) {
        return first.getState() < second.getState();
    }
};

/**
 * A priority_queue wrapped by a class for the purpose of including a set
 * that will allow us to check if an element is in the the q in constant complexity.
 * The class inherits priority_queue.
 *
 * Important!!!
 *      The priority_queue comparator is a heuristicDistance comparator,
 *          since the overridden operators in state are cost related there is no need for defining the comparator.
 *      The set comparator is a position comparator.
 */
template <typename E>
class HashPriorityQueueBestFirstSearch : public priority_queue<E> {
private:
    set<E, positionComparator<E>> mySet;// POSITION_COMPARED
    int missed_inserts = 0;
public:
    void insert(E element);
    E topAndPop();
    bool contains(E element);
    E find(E element);
    void remove(E element);
};

template class HashPriorityQueueBestFirstSearch<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEBESTFIRSTSEARCH_H
