//
// Created by Dor Refaeli on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEBESTFIRSTSEARCH_H
#define ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEBESTFIRSTSEARCH_H

#include <stdio.h>
#include <algorithm>
#include <iostream>
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
 *      The priority_queue comparator is a heuristicDistance comparator,
 *          since the overridden operators in state are cost related there is no need for defining the comparator.
 *      The set comparator is a position comparator.
 */
template <typename P>
class HashPriorityQueueBestFirstSearch : public priority_queue<P, vector<P>, costComparator<P>> {
private:
    set<P, positionComparator<P>> mySet;// POSITION_COMPARPE
    int missed_inserts = 0;

public:
    void insert(P element);
    void remove(P element);
    bool contains(P element);
    P find(P element);
    P topAndPop();
};

template class HashPriorityQueueBestFirstSearch<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEBESTFIRSTSEARCH_H
