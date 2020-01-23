//
// Created by Dor Refaeli on 21/01/2020.
//

#include <iostream>
#include <stack>
#include <set>

#include "DFS.h"

using namespace std;

/**
 * searches for a solution by using the depth first search algorithm
 * @tparam P the nodes that represents the Searchable (State<Point> in our case)
 * @param problem an object of type searchable (SearchableMatrix in our case)
 * @return list of nodes of type P describing the route to the solution
 */
template <class P>
list<P>* DFS<P>::search(Searchable<P> *problem) {
    cout << "Started DFS" << endl;/*TODO debug*/
    auto special_case_result = new list<P>();

    /*Returns empty list if goal or initial are walls.*/
    if(!(Searcher<P>::isValid(problem))) {
        cout << "Goal or initial is (-1)" << endl; /*TODO debug*/
        cout << "Ended DFS" << endl; /*TODO debug*/
        return special_case_result;
    }

    /*Case initial is goal*/
    if(problem->isGoalState(problem->getInitialState())) {
        special_case_result->push_back(problem->getInitialState());
        cout << "Goal is initial state" << endl; /*TODO debug*/
        cout << "Ended DFS" << endl; /*TODO debug*/
        return special_case_result;
    }

    stack<P> statesStack;/*TODO wy stack State<Point> and not P? P is State<Point> in our case*/
    /*TODO: brought "typename" back, not sure if its good.*/
    //the existence of a State in this set indicates he was discovered already
    set<P, positionComparator<P>> visitedSet;
    P initial = problem->getInitialState();
    statesStack.push(initial);
    while (!statesStack.empty()) {
        P current = statesStack.top();
        statesStack.pop();
        if (problem->isGoalState(current)) {
            cout << "Found the goal state" << endl; /*TODO debug*/
            cout << "End DFS" << endl; /*TODO debug*/
            return current.backtrace();
        }
        //if not in visited Set
        if (!visitedSet.count(current)) {
            visitedSet.insert(current);
            list<P> adjacents = problem->getAllPossibleStates(current);
            for (auto adjacent : adjacents) {
                if (!visitedSet.count(adjacent)) {
                    statesStack.push(adjacent);
                }
            }
        }
    }

    /*Return empty list if no path found*/
    cout << "No path found" << endl; /*TODO debug*/
    cout << "End DFS" << endl; /*TODO debug*/
    return special_case_result;
}
template<class P>
Searcher<P> *DFS<P>::clone() const {
    return new DFS<P>();
}