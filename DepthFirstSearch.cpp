//
// Created by Dor Refaeli on 21/01/2020.
//

#include <iostream>
#include <stack>
#include <set>

#include "DepthFirstSearch.h"

using namespace std;

template <class P>
list<P> DepthFirstSearch<P>::search(Searchable<P> *problem) {
    cout << "Started DepthFirstSearch" << endl;
    stack<State<Point>> statesStack;/*TODO wy stack State<Point> and not P? P is State<Point> in our case*/
    /*TODO: brought "typename" back, not sure if its good.*/
    //the existence of a State in this set indicates he was discovered already
    set<State<P>, typename State<P>::positionComparator> visitedSet;
    P initial = problem->getInitialState();
    statesStack.push(initial);
    while (!statesStack.empty()) {
        P current = statesStack.top();
        statesStack.pop();
        if (problem->isGoalState(current)) {
            return current;
        }
        if (!visitedSet.count(current)) {
            visitedSet.insert(current);
            /*TODO: had this line below, you had a list of S (Solutions), we changed Solution to be
             * list<P>.
             * Was is wrong (the S in adjacents) or not?
             * If not than we need to change list<P> to list<list<P>>.
             *list<S> adjacents = problem->getAllPossibleStates(current);*/
            list<P> adjacents = problem->getAllPossibleStates(current);
            for (auto adjacent : adjacents) {
                if (!visitedSet.count(adjacent)) {
                    statesStack.push(adjacent);
                }
            }
        }
    }
}