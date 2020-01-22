//
// Created by doref on 19/01/2020.
//

#include <set>
#include <iostream>

#include "HashPriorityQueueBestFirstSearch.h"
#include "BestFirstSearch.h"

using namespace std;

/**
 *
 * @tparam P
 * @param problem
 * @return
 */
template <class P>
list<P> BestFirstSearch<P>::search(Searchable<P> *problem) {
    cout<<"Started BestFirstSearch"<<endl;
    HashPriorityQueueBestFirstSearch<P> open;
    /*TODO: brought "typename" back, not sure if its good.*/
    set<P, typename P::positionComparator> closed;
    open.insert(problem->getInitialState());
    while (!open.empty()) {
        this->evaluatedNodesCount++; //TODO: remove?
        // n <- dequeue open
        P n = open.topAndPop();
        cout<<"Before: "<<closed.count(n)<<endl;
        // add n to closed
        closed.insert(n);
        cout<<"After: "<<closed.count(n)<<endl;
        // if n is the goal state
        if (problem->isGoalState(n)) {
            cout<<"Found the goal state"<<endl;
            //backtrace the route that got you to n and return it as list
            return *(n.backtrace());
        }
        // creates n's successors
        auto successors = problem->getAllPossibleStates(n);
        // for each successor s do
        for (auto s : successors) {
            // if not in closed and not in open
            if (!closed.count(s) && !open.contains(s)) {
                // add s to open, s's prev is already updated
                open.insert(s);
            // if in closed or in open
            } else {
                // get the vertex himself
                P before;
                if (open.contains(s)) {
                    before = open.find(s);
                } else {
                    before = *(closed.find(s));
                }
                // if better then the previous
                if (s < before) {
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

    /*TODO: If algorithm didnt reach goal_state?*/
    return list<P>();
}
template<class P>
Searcher<P> *BestFirstSearch<P>::clone() const {
    return new BestFirstSearch<P>();
}
