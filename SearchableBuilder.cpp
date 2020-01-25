//
// Created by Omer Mizrachi on 19/01/2020.
//

#include "SearchableBuilder.h"

/** Builds a SearchableMatrix object.
 *
 * @tparam State<Point>
 * @param data list of string, each line represents a row in the matrix (int)
 * seperated by ','.
 * @return Matrix.
 */
template <class P>
SearchableMatrix<P>* SearchableBuilder<P>::buildMatrix(list<string> data) {
    auto sMatrix = new SearchableMatrix<P>;
    int row_index=0, col_index=0;
    P *initial, *goal;
    string special_state;
    regex intRx("(-?\\d+)");

    /*Double check "end" didnt sneak in*/
    if(strstr(data.rbegin()->c_str(), "end")) {
        data.pop_back();
    }

    /*Goal state*/
    goal = buildMatrixState(data.rbegin()->c_str());
    data.pop_back();

    /*Initial state*/
    initial = buildMatrixState(data.rbegin()->c_str());
    data.pop_back();

    /*Iterates data list. Each string represents a ROW in the matrix*/
    for(auto row_iter = data.begin(); row_iter != data.end(); ++row_iter, ++row_index, col_index=0) {
        /*Init new row's vector*/
        auto row = new vector<P>;
        int cost;

        /*Regex iterators to match each integer in parsed string*/
        auto start = sregex_iterator(row_iter->begin(), row_iter->end(), intRx);
        auto end = sregex_iterator();

        /*Iterates columns. Each string represents a cell's COST in the matrix*/
        for (sregex_iterator cols_iter = start; cols_iter != end; ++cols_iter, ++col_index) {
            string cost_str = cols_iter->str();
            try {
                cost = stol(cost_str);
            } catch (const char* e) {
                delete row;
                delete sMatrix;
                return nullptr;
            }

            /*Build cell (State<Point>) and push to the end of current row*/
            P* cur_cell = buildMatrixCell(row_index, col_index, cost, nullptr);

            /*Error occurred*/
            if(cur_cell == nullptr) {
                delete row;
                delete sMatrix;
                return nullptr;
            }

            /*Handle special cases accordingly*/
            if(cur_cell->getState() == initial->getState()) {
                /*If initial_state is not a node*/
                if(cost == -1) {
                    sMatrix->setInitialState(*cur_cell);
                }
                sMatrix->setInitialState(*initial);
            }
            if(cur_cell->getState() == goal->getState()) {
                sMatrix->setGoalState(*goal);
            }
            row->push_back(*cur_cell);
        }
        sMatrix->addRow(row);
    }
    return sMatrix;
}

/** Builds matrix state, used for initial or goal.
 *
 * @param state_str
 * @return
 */
template <class P>
P* SearchableBuilder<P>::buildMatrixState(string state_str) {
    regex intRx("(-?\\d+)");
    smatch match;
    int x, y;

    sregex_iterator it = sregex_iterator(state_str.begin(), state_str.end(), intRx);
    try {
        x = stoi(it->str());
        ++it;
        y = stoi(it->str());
    } catch (const char* e) {
        perror("buildMatrixState"); /*TODO debug*/
        perror(e);
        exit(EXIT_FAILURE);
    }
    return buildMatrixCell(x,y, 0, nullptr);
}

/** Cell in our case is a State<P>, a point with cost.
 *  NOTE: prev should be nullptr as for this part.
 *
 * @param row index
 * @param col index
 * @param cost
 * @param prev should be null ptr
 * @return
 */
template <class P>
P* SearchableBuilder<P>::buildMatrixCell(int row, int col, int cost, P *prev) {
    /*TODO next assignments, need to find better solution for this generic type
     * P C'TOR. maybe make sure p has a specific C'TOR, can use strings and builder
     * DP*/
    return new P(row, col, cost, prev);
}


