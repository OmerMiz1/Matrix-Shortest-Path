//
// Created by Dor Refaeli on 20/01/2020.
//

#include <iostream>
#include <queue>
#include <set>

#include "BreadthFirstSearch.h"

using namespace std;

template <class P, class S>
S BreadthFirstSearch<P,S>::search(Searchable<P> problem) {
    cout << "Started BreadthFirstSearch" << endl;
    queue<State<P>> statesQueue;
    /*TODO: brought "typename" back, not sure if its good.*/
    //the existence of a State in this set indicates he was discovered already
    set<State<P>, typename State<P>::positionComparator> discoveredSet;
    S initial = problem.getInitialState();
    discoveredSet.insert(initial);
    statesQueue.push(initial);
    while (!statesQueue.empty()) {
        S current = statesQueue.front();
        statesQueue.pop(); //TODO couldn't make sure that front doesn't pop already! make sure
        if (problem.isGoalState(current)) {
            return current;
        }
        list<S> adjacents = problem.getAllPossibleStates(current);
        for (auto adjacent : adjacents) {
            if (!discoveredSet.count(adjacent)) { //if the adjacent wasn't discovered yet
                discoveredSet.insert(adjacent);
                /**
                 * In original algorithm at this point we would set adjacent.parent = current,
                 * this happens automatically when we call problem.getAllPossibleStates(current)
                 */
                statesQueue.push(adjacent);
            }
        }
    }
}