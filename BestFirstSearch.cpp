//
// Created by doref on 19/01/2020.
//

#include <set>
#include <iostream>

#include "HashPriorityQueue.h"
#include "BestFirstSearch.h"

using namespace std;

/**
 *
 * @tparam P
 * @param problem
 * @return
 */
template <class P, class S>
S BestFirstSearch<P,S>::search(P problem) {
    cout<<"Started BestFirstSearch"<<endl;
    HashPriorityQueue<P> open;
    set<State<P>, typename State<P>::positionComparator> closed; /*TODO: brought "typename" back, not sure if its good.*/
    open.insert(problem.getInitialState());
    while (!open.empty()) {
        this->evaluatedNodesCount++;
        // n <- dequeue open
        State<P> n = open.topAndPop();
        cout<<"Before: "<<closed.count(n)<<endl;
        // add n to closed
        closed.insert(n);
        cout<<"After: "<<closed.count(n)<<endl;
        // if n is the goal state
        if (problem.isGoalState(n)) {
            cout<<"Found the goal state"<<endl;
            //backtrace the route that got you to n and return it as list
            return n;
        }
        // creates n's successors
        auto successors = problem.getAllPossibleStates(n);
        // for each successor s do
        for (auto s : successors) {
            // if not in closed and not in open
            if (!closed.count(s) && !open.contains(s)) {
                // add s to open, s's prev is already updated
                open.insert(s);
            // if in closed or in open
            } else {
                // get the vertex himself
                State<P> before;
                if (open.contains(s)) {
                    before = open.find(s);
                } else {
                    before = *(closed.find(s));
                }
                // if better then the previous
                if (before < s) {
                    //if s not in open add it
                    if (!open.contains(s)) {
                        open.insert(s);
                    //if s in open update him
                    } else {
                        open.remove(before);
                        open.insert(s);
                    }
                }
            }
        }
    }
}