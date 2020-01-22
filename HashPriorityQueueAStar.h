//
// Created by Dor Refaeli on 21/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEASTAR_H
#define ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEASTAR_H

#include <queue>
#include <set>
#include "State.h"

using namespace std;

template <typename E>
class heuristicDistanceComparator {
    bool operator()(const E &lhs, const E &rhs) const {
        return lhs.second < rhs.second;
    }
};

template <typename E>
class pairPositionComparator {
    bool operator()(const E &lhs, const E &rhs) const {
        return lhs.first.getState() < rhs.first.getState();
    }
};

/**
 * A priority_queue wrapped by a class for the purpose of including a set
 * that will allow us to check if an element is in the the q in constant complexity.
 * The class inherits priority_queue.
 *
 * Important!!!
 *      The priority_queue comparator is a heuristicDistance comparator.
 *      The set comparator is a position comparator.
 */
template <typename E>
class HashPriorityQueueAStar : public priority_queue<pair<E,double>, vector<pair<E,double>>, heuristicDistanceComparator<E>> {
private:
    set<pair<E,double>, pairPositionComparator<E>> mySet;// POSITION_COMPARED
    int missed_inserts = 0;
public:
    void insert(pair<E,double> element);
    pair<E,double> topAndPop();
    bool contains(pair<E,double> element);
    pair<E,double> find(pair<E,double> element);
    void remove(pair<E,double> element);
};

template class HashPriorityQueueAStar<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEASTAR_H
