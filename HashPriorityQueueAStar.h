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
template <typename P>
class HashPriorityQueueAStar : public priority_queue<pair<P,double>, vector<pair<P,double>>, HeuristicDistanceComparator<pair<P, double>>> {
private:
    set<pair<P,double>, PairPositionComparator<pair<P, double>>> my_set;// POSITION_COMPARED
    unsigned int evaluated_nodes =0;
    int missed_inserts = 0;
public:
    void insert(pair<P,double> element);
    pair<P,double> topAndPop();
    bool contains(pair<P,double> element);
    pair<P,double> find(pair<P,double> element);
};

template class HeuristicDistanceComparator<pair<State<Point>,double>>;
template class PairPositionComparator<pair<State<Point>,double>>;
template class HashPriorityQueueAStar<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_HASHPRIORITYQUEUEASTAR_H
