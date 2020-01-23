//
// Created by Dor Refaeli on 19/01/2020.
//

#include <set>
#include <iostream>

#include "HashPriorityQueueBestFirstSearch.h"
#include "BestFS.h"

using namespace std;

/**
 * searches for a solution by using the best first search algorithm
 * @tparam P the nodes that represents the Searchable (State<Point> in our case)
 * @param problem an object of type searchable (SearchableMatrix in our case)
 * @return list of nodes of type P describing the route to the solution
 */
template<class P>
list<P> *BestFS<P>::search(Searchable<P> *problem) {
    cout << "Started BestFS" << endl; /*TODO debug*/
    auto special_case_result = new list<P>();

    /*Returns empty list if goal or initial are walls.*/
    if (!(Searcher<P>::isValid(problem))) {
        cout << "Goal or initial is (-1)" << endl; /*TODO debug*/
        cout << "Ended BestFS" << endl; /*TODO debug*/
        return special_case_result;
    }

    /*Case initial is goal*/
    if (problem->isGoalState(problem->getInitialState())) {
        special_case_result->push_back(problem->getInitialState());
        cout << "Goal is initial state" << endl; /*TODO debug*/
        cout << "Ended BestFS" << endl; /*TODO debug*/
        return special_case_result;
    }

    //TODO remove!!!
    char x = problem->getInitialState().getState().getX() + 'A';
    int y = problem->getInitialState().getState().getY()+1;
    clog << "Initial state is: " << x << "," << y << endl;
    x = problem->getGoalState().getState().getX() + 'A';
    y = problem->getGoalState().getState().getY()+1;
    clog << "Goal state state is: " << x << "," << y << endl;

    /*Initialize open/closed*/
    HashPriorityQueueBestFirstSearch<P> open;
    set<P, typename P::positionComparator> closed;

    //add the initial state to the queue
    open.insert(problem->getInitialState());
    //while the queue isn't empty
    while (!open.empty()) {
        this->evaluatedNodesCount++; //TODO: remove?
        // n <- dequeue open
        P n = open.topAndPop();

        //TODO remove
        char x = n.getState().getX() + 'A';
        int y = n.getState().getY()+1;
        int cost = n.getCost();
        clog << "lowest cost in queue is: " << x << "," << y << " - with cost: " << cost << endl;
        // add n to the the set of "closed"\already-visited nodes
        closed.insert(n);

        // if n is the goal state
        if (problem->isGoalState(n)) {
            cout << "Found the goal state" << endl; /*TODO debug*/
            cout << "Ended BestFS" << endl; /*TODO debug*/
            return n.backtrace();
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

    /*Return empty list no path found*/
    cout << "No path found" << endl; /*TODO debug*/
    cout << "Ended BestFS" << endl; /*TODO debug*/
    return special_case_result;}
template<class P>
Searcher<P> *BestFS<P>::clone() const {
    return new BestFS<P>();
}
