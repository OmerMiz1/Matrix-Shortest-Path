//
// Created by Dor Refaeli on 21/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_ASTAR_H
#define ALGORITHMICPROGRAMMING2_ASTAR_H

#include "Searcher.h"
#include "Searchable.h"
#include "State.h"

template <class P>
class AStar : Searcher<P> {
private:
    P goal;
    double heuristicDistance(State<P> current, State<P> goal);
public:
    AStar(P goal_state):goal(goal_state) {}
    list<P> search(Searchable<P> problem) override;
};


#endif //ALGORITHMICPROGRAMMING2_ASTAR_H
