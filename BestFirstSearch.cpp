//
// Created by doref on 19/01/2020.
//

#include <set>
#include <iostream>
#include "HashPriorityQueue.h"
#include "BestFirstSearch.h"

using namespace std;

template<typename P, typename S>
S BestFirstSearch<P, S>::solve(P problem) {
    return nullptr;
}

template<>
list<Vertex> BestFirstSearch<Searchable<Point>,list<Vertex>>::solve(Searchable<Point> problem) {
    cout<<"Started BestFirstSearch"<<endl;
    HashPriorityQueue<Point> open;
    set<Vertex, State<Point>::positionComparator> closed;
    open.insert(problem.getInitialState());
    while (!open.empty()) {
        this->evaluatedNodesCount++;
        // n <- dequeue open
        State<Point> n = open.topAndPop();
        cout<<"Before: "<<closed.count(n)<<endl;
        // add n to closed
        closed.insert(n);
        cout<<"After: "<<closed.count(n)<<endl;
        // if n is the goal state
        if (problem.isGoalState(n)) {
            cout<<"Found the goal state"<<endl;
            list<Vertex> backtrace;
            //backtrace the route that got you to n and return it as list
            return n.backtrace();
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
                Vertex before;
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