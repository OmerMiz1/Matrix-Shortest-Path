//
// Created by Dor Refaeli on 19/01/2020.
//

#include <set>
#include <iostream>

#include "HashPriorityQueueBestFirstSearch.h"
#include "BestFirstSearch.h"

using namespace std;

/**
 * searches for a solution by using the best first search algorithm
 * @tparam P the nodes that represents the Searchable (State<Point> in our case)
 * @param problem an object of type searchable (SearchableMatrix in our case)
 * @return list of nodes of type P describing the route to the solution
 */
template <class P>
list<P> BestFirstSearch<P>::search(Searchable<P> *problem) {
    cout<<"Started BestFirstSearch"<<endl;
    //the priority queue of nodes to be checked
    HashPriorityQueueBestFirstSearch<P> open;
    //the set of "closed"\already-visited nodes
    /*TODO: brought "typename" back, not sure if its good.*/
    set<P, typename P::positionComparator> closed;
    //add the initial state to the queue
    open.insert(problem->getInitialState());
    //while the queue isn't empty
    while (!open.empty()) {
        this->evaluatedNodesCount++; //TODO: remove?
        // n <- dequeue open
        P n = open.topAndPop();
        cout<<"Before: "<<closed.count(n)<<endl; //TODO remove before submitting
        // add n to the the set of "closed"\already-visited nodes
        closed.insert(n);
        cout<<"After: "<<closed.count(n)<<endl; //TODO remove before submitting
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
    //return an empty list if the queue is empty and didn't got to goal state
    /*TODO: If algorithm didnt reach goal_state?*/
    return list<P>();
}
template<class P>
Searcher<P> *BestFirstSearch<P>::clone() const {
    return new BestFirstSearch<P>();
}
