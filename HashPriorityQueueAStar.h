//
// Created by Dor Refaeli on 21/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEASTAR_H
#define ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEASTAR_H

#include <queue>
#include <set>

#include "State.h"

using namespace std;

template <typename P>
class HeuristicDistanceComparator {
 public:
    bool operator()(const P &lhs, const P &rhs) const {
        return lhs.second < rhs.second;
    }
};

template <typename P>
class PairPositionComparator {
 public:
    bool operator()(const P &lhs, const P &rhs) const {
        return lhs.first.getState().uniq() < rhs.first.getState().uniq();
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
template <typename P>
class HashPriorityQueueAStar : public priority_queue<pair<P,int>, vector<pair<P,int>>, HeuristicDistanceComparator<pair<P, int>>> {
private:
    set<pair<P,int>, PairPositionComparator<pair<P, int>>> my_set;// POSITION_COMPARED
    unsigned int evaluated_nodes =0;

public:
    void insert(pair<P,int> element);
    bool contains(pair<P,int> element);
    pair<P,int> topAndPop();
    pair<P,int> find(pair<P,int> element);
};

template class HeuristicDistanceComparator<pair<State<Point>,int>>;
template class PairPositionComparator<pair<State<Point>,int>>;
template class HashPriorityQueueAStar<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEASTAR_H
