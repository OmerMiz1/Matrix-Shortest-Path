//
// Created by omer on 19/01/2020.
//

#include "SearchableBuilder.h"

template <class P>
SearchableMatrix<P>* SearchableBuilder<P>::buildMatrix(list<string> data) {
    auto sMatrix = new SearchableMatrix<P>;
    Point initial, goal;
    int row_index=0, col_index=0;
    regex intRx("(-?\\d+)");

    auto it = data.rbegin();
    /*Double check "end" didnt sneak in*/
    if(!it->compare("end")) {
        ++it;
        data.pop_back();
    }

    /*Initial state*/
    initial = buildMatrixState(*it);
    ++it;
    data.pop_back();

    /*Goal state*/
    goal = buildMatrixState(*it);
    data.pop_back();

    /*Iterates data list. Each string represents a ROW in the matrix*/
    for(auto row_iter = data.begin(); row_iter != data.end(); ++row_iter, ++row_index, col_index=0) {
        auto row = new vector<State<P>>;
        double cost;

        /*Regex iterators to match each integer in parsed string*/
        auto start = sregex_iterator(row_iter->begin(), row_iter->end(), intRx);
        auto end = sregex_iterator();

        /*Iterates columns. Each string represents a cell's COST in the matrix*/
        for (sregex_iterator cols_iter = start; cols_iter != end; ++cols_iter, ++col_index) {
            string cost_str = cols_iter->str();
            try {
                cost = stol(cost_str);
            } catch (const char* e) {
                perror("buildMatrix");
                perror(e);
                /*TODO: debug*/
                clog<<"row_index: "<<row_index<<"col_index: "<<col_index<<endl;
                delete sMatrix;
                return nullptr;
            }
            auto cur_cell = buildMatrixCell(row_index, col_index, cost, nullptr);
            row->push_back(cur_cell);
        }
        sMatrix->addRow(row);
    }

    sMatrix->setInitialState(initial);
    sMatrix->setGoalState(goal);
    return sMatrix;
}

/** Builds matrix state - in our case its a Point.
 *  Used to parse initial point and goal point.
 *
 * @param state_str
 * @return
 */
template <class P>
P SearchableBuilder<P>::buildMatrixState(string state_str) {
    regex intRx("(-?\\d+)");
    smatch match;
    int x, y;

    auto it = sregex_iterator(state_str.begin(), state_str.end(), intRx);
    try {
        x = stoi(it->str());
        ++it;
        y = stoi(it->str());
    } catch (const char* e) {
        perror("buildMatrixState"); /*TODO debug*/
        perror(e);
        exit(EXIT_FAILURE);
    }
    return P(x,y);

}

/** Cell in our case is a State<P>, a point with cost.
 *  NOTE: prev should be nullptr as for now.
 *
 * @param row index
 * @param col index
 * @param cost
 * @param prev should be null ptr
 * @return
 */
template <class P>
State<P> SearchableBuilder<P>::buildMatrixCell(int row, int col, double cost, State<P> *prev) {
    /*TODO next assignments, need to find better solution for this generic type
     * P C'TOR. maybe make sure p has a specific C'TOR, can use strings and builder
     * DP*/
    auto cur_cell = new P(row, col);
    return State<P>(cur_cell, cost, prev);
}


