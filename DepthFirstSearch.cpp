//
// Created by Dor Refaeli on 21/01/2020.
//

#include <iostream>
#include <stack>
#include <set>

#include "DepthFirstSearch.h"

using namespace std;

template <class P, class S>
S DepthFirstSearch<P,S>::search(Searchable<P> problem) {
    cout << "Started DepthFirstSearch" << endl;
    stack<State<Point>> statesStack;
    /*TODO: brought "typename" back, not sure if its good.*/
    //the existence of a State in this set indicates he was discovered already
    set<State<P>, typename State<P>::positionComparator> visitedSet;
    S initial = problem.getInitialState();
    statesStack.push(initial);
    while (!statesStack.empty()) {
        S current = statesStack.top();
        statesStack.pop();
        if (problem.isGoalState(current)) {
            return current;
        }
        if (!visitedSet.count(current)) {
            visitedSet.insert(current);
            list<S> adjacents = problem.getAllPossibleStates(current);
            for (auto adjacent : adjacents) {
                if (!visitedSet.count(adjacent)) {
                    statesStack.push(adjacent);
                }
            }
        }
    }
}