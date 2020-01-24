//
// Created by Dor Refaeli on 21/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_ASTAR_H
#define ALGORITHMICPROGRAMMING2_ASTAR_H

#include "Searcher.h"
#include "Searchable.h"
#include "State.h"

template <class P>
class AStar : public Searcher<P> {
private:
    P initial;
    P goal;
    int heuristicDistance(P current);
public:
    list<P>* search(Searchable<P> *problem) override;
    Searcher<P> *clone() const override;
};

template class AStar<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_ASTAR_H
