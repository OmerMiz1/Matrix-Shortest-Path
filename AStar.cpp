//
// Created by Dor Refaeli on 21/01/2020.
//

#include <iostream>
#include <map>

#include "AStar.h"
#include "HashPriorityQueueAStar.h"

using namespace std;

template <class P, class S>
S AStar<P,S>::search(Searchable<P> problem) {
    cout << "Started A-Star" << endl;
    HashPriorityQueueAStar<P> open;
    set<State<P>, typename State<P>::positionComparator> closed;
    map<State<P>, int, typename State<P>::positionComparator> heuristic;
    State<P> initialState = problem.getInitialState();
    State<P> goalState = problem.getGoalState();
    class heuristicDistanceComparator {
        bool operator()(pair<State<Point>, double> &lhs, pair<State<Point>, double> &rhs) {
            return lhs.second < rhs.second;
        }
    };

}

template<class P, class S>
double AStar<P, S>::heuristicDistance(State<P> current, State<P> goal) {
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
