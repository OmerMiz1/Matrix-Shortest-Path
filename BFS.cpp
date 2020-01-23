//
// Created by Dor Refaeli on 20/01/2020.
//

#include <iostream>
#include <queue>
#include <set>

#include "BFS.h"

using namespace std;

/*template <class P>
class positionComparator {
    bool operator()(const P& first, const P& second) const {
        return first.getState() < second.getState();
    }
};*/
/*
template <typename E>
class positionComparator {
    bool operator()(const E &first, const E &second) {
        return first.getState() < second.getState();
    }
};*/

/**
 * searches for a solution by using the breadth first search algorithm
 * @tparam P the nodes that represents the Searchable (State<Point> in our case)
 * @param problem an object of type searchable (SearchableMatrix in our case)
 * @return list of nodes of type P describing the route to the solution
 */
template <class P>
list<P>* BFS<P>::search(Searchable<P> *problem) {
    cout << "Started BFS" << endl;
    auto special_case_result = new list<P>();

    /*Returns empty list if goal or initial are walls.*/
    if(!(Searcher<P>::isValid(problem))) {
        cout << "Goal or initial is (-1)" << endl; /*TODO debug*/
        cout << "Ended BFS" << endl; /*TODO debug*/
        return special_case_result;
    }

    /*Case initial is goal*/
    if(problem->isGoalState(problem->getInitialState())) {
        special_case_result->push_back(problem->getInitialState());
        cout << "Goal is initial state" << endl; /*TODO debug*/
        cout << "Ended BFS" << endl; /*TODO debug*/
        return special_case_result;
    }

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
            cout << "Found the goal state" << endl; /*TODO debug*/
            cout << "Ended BFS" << endl; /*TODO debug*/
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

    /*Return empty list no path found*/
    cout << "No path found" << endl; /*TODO debug*/
    cout << "Ended BFS" << endl; /*TODO debug*/
    return special_case_result;
}
template<class P>
Searcher<P> *BFS<P>::clone() const {
    return new BFS<P>();
}
