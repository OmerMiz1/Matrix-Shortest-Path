//
// Created by Dor Refaeli on 21/01/2020.
//

#include <iostream>

#include "AStar.h"
#include "HashPriorityQueueAStar.h"

using namespace std;

template <class P>
list<P>* AStar<P>::search(Searchable<P> *problem) {
    cout << "Started AStar" << endl; /*TODO debug*/
    auto special_case_result = new list<P>();

    /*Returns empty list if goal or initial are walls.*/
    if(!(Searcher<P>::isValid(problem))) {
        cout << "Goal or initial is (-1)" << endl; /*TODO debug*/
        cout << "Ended AStar" << endl; /*TODO debug*/
        return special_case_result;
    }

    /*Case initial is goal*/
    if(problem->isGoalState(problem->getInitialState())) {
        special_case_result->push_back(problem->getInitialState());
        cout << "Goal is initial state" << endl; /*TODO debug*/
        cout << "Ended AStar" << endl; /*TODO debug*/
        return special_case_result;
    }

    /*Init open list and closed list*/
    HashPriorityQueueAStar<P> open;
    set<pair<P, int>, PairPositionComparator<pair<P,int>>> closed;

    /*current is poped from open list.
     *current_g is q.g.*/
    pair<P,int> current, cur_pos_best_f_node;
    int succsessor_g, succsessor_h, succsessor_f, current_g, cur_pos_best_f;

    /*Extract initial and goal states from problem (Matrix)*/
    initial = problem->getInitialState();
    goal = problem->getGoalState();

    /*Push INITIAL state to OPEN list, first 'f' is set to 0 */
    auto init_pair = make_pair(initial, static_cast<int>(0));
    open.insert(init_pair);

    /*If open is empty then it means no path. Loop may also break if reached solution.*/
    while (!open.empty()) {
        current = open.topAndPop();
        current_g = abs(current.first.getCost()-current.first.getPrevCost());
        /*Iterate successors. 's' should be State<Point> / node....*/
        for (auto s : problem->getAllPossibleStates(current.first)) {
            /*Goal found (succsessor is goal state )*/
            if (problem->isGoalState(s)) {
                cout << "Found the goal state" << endl; /*TODO debug*/
                cout << "Ended AStar" << endl; /*TODO debug*/
                return current.first.backtrace();
            }

            /*Init successor with heu distance*/
            int s_heu = heuristicDistance(s);
            auto succsessor = make_pair(s, s_heu);

            succsessor_g = (current.first.getCost() + current_g);
            succsessor_h = heuristicDistance(s);
            succsessor_f = succsessor_g + succsessor_h;

            /*Check for node in open that has same position*/
            if(open.contains(succsessor)) {
                cur_pos_best_f = open.find(succsessor).second;
                /*If the f value of that node is smaller, skip cur succsessor.*/
                if(cur_pos_best_f < succsessor_f) {
                    continue;
                }
            }

            /*Check for node in closed that has same position*/
            if(closed.count(succsessor)) {
                cur_pos_best_f = closed.find(succsessor)->second;
                if(cur_pos_best_f < succsessor_f) {
                    continue;
                }
            }

            /*O.W.*/
            open.insert(succsessor);
        } // End successors loop

        closed.insert(current);
    }// End while (Open is not empty)

    /*No path found - returns an empty list.*/
    cout << "No path found" << endl; /*TODO debug*/
    cout << "Ended AStar" << endl; /*TODO debug*/
    return special_case_result;
}
template<class P>
Searcher<P> *AStar<P>::clone() const {
    return new AStar<P>();
}

template<class P>
int AStar<P>::heuristicDistance(P current) {
    Point currentPoint = current.getState();
    Point goalPoint = goal.getState();
    return currentPoint.manhattanHeuristicDistance(&goalPoint);
}
