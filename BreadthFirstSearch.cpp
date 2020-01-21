//
// Created by Dor Refaeli on 20/01/2020.
//

#include <iostream>
#include <queue>
#include <set>

#include "BreadthFirstSearch.h"

using namespace std;

/*template <class P>
class positionComparator {
    bool operator()(const P& first, const P& second) const {
        return first.getState() < second.getState();
    }
};*/

template <typename E>
class positionComparator {
    bool operator()(const E &first, const E &second) {
        return first.getState() < second.getState();
    }
};

template <class P>
list<P> BreadthFirstSearch<P>::search(Searchable<P> *problem) {
    cout << "Started BreadthFirstSearch" << endl;
    queue<P> statesQueue;
    /*TODO: brought "typename" back, not sure if its good.*/
    //the existence of a State in this set indicates he was discovered already
    set<P, positionComparator<P>> discoveredSet;
    P initial = problem->getInitialState();
    discoveredSet.insert(initial);
    statesQueue.push(initial);
    while (!statesQueue.empty()) {
        P current = statesQueue.front();
        statesQueue.pop(); //TODO couldn't make sure that front doesn't pop already! make sure
        if (problem->isGoalState(current)) {
            return current.backtrace();
        }

        /*TODO: had this line below, you had a list of S (Solutions), we changed Solution to be
         * list<P>.
         * Was is wrong (the S in adjacents) or not?
         * If not than we need to change list<P> to list<list<P>>.
         *list<S> adjacents = problem.getAllPossibleStates(current);*/
        list<P> adjacents = problem->getAllPossibleStates(current);
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