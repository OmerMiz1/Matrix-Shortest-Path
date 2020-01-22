//
// Created by Dor Refaeli on 21/01/2020.
//

#include <iostream>
#include <map>

#include "AStar.h"
#include "HashPriorityQueueAStar.h"

using namespace std;

template <class P>
list<P> AStar<P>::search(Searchable<P> problem) {
    cout << "Started A-Star" << endl;
    HashPriorityQueueAStar<P> open;
    set<pair<P, double>, typename P::positionComparator> closed; //TODO Build new comparator
    State<P> initialState = problem.getInitialState();
    State<P> goalState = problem.getGoalState();
    open.push(make_pair(initialState,heuristicDistance(initialState, goalState)));
    while (!open.empty()) {
        pair<P,double> current = open.topAndPop().first;
        closed.insert(current);
        if (problem.isGoalState(current)) {
            cout << "Found the goal state" << endl;
            return *(current.backtrace());
        }
        auto successors = problem->getAllPossibleStates(current);
        for (auto s : successors) {
            if (!closed.count(make_pair(s,0)) && !open.contains(make_pair(s,0))) {
                // add s to open, s's prev is already updated
                open.insert(make_pair(s, heuristicDistance(s, goalState) + s.first.getCost()));
                // if in closed or in open
            } else {
                // get the vertex himself
                P before;
                if (open.contains(make_pair(s,0))) {
                    before = open.find(make_pair(s,0));
                } else {
                    before = *(closed.find(make_pair(s,0)));
                }
                // if better then the previous
                if (s < before) {
                    //if s not in open add it
                    if (!open.contains(make_pair(s,0))) {
                        open.insert(make_pair(s,heuristicDistance(s, goalState) + s.first.getCost()));
                    //if s in open update him
                    } else {
                        open.remove(make_pair(before,0));
                        open.insert(make_pair(s,heuristicDistance(s, goalState) + s.first.getCost()));
                    }
                }
            }
        }
    }
    return list<P>(); // returns empty list if there is no route from initial state to goal state
}
template<class P>
Searcher<P> *AStar<P>::clone() const {
    return new AStar<P>();
}

template<class P>
double AStar<P>::heuristicDistance(State<P> current, State<P> goal) {
    Point* currentPoint = dynamic_cast<Point*>(current.getState());
    if (!currentPoint) {
        perror("Tried calculating a heuristic distance of non-point type");
    }
    Point* goalPoint = dynamic_cast<Point*>(goal.getState());
    if (!goalPoint) {
        perror("Tried calculating a heuristic distance of non-point type");
    }
    return currentPoint->distance(goalPoint);
}
