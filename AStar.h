//
// Created by Dor Refaeli on 21/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_ASTAR_H
#define ALGORITHMICPROGRAMMING2_ASTAR_H

#include "Searcher.h"
#include "Searchable.h"
#include "State.h"

template <class P, class S>
class AStar {
public:
    S search(Searchable<P> problem) override;

private:
    double heuristicDistance(State<P> current, State<P> goal);
};


#endif //ALGORITHMICPROGRAMMING2_ASTAR_H
