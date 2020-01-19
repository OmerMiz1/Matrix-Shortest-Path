//
// Created by omer on 19/01/2020.
//

#include "SearcheableBuilder.h"

template <class P, class S>
Searchable<P>* SearcheableBuilder<P,S>::buildMatrix(list<string> data) {
    auto sMatrix = new SearchableMatrix;
    Point *initial, *goal;
    int row_index=0, col_index=0;
    regex intRx("(-?\\d+)");

    auto it = data.rbegin();
    /*Double check "goal" didnt sneak in*/
    if(!it->compare("goal")) {
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
        auto row = new vector<Vertex>;
        int cost;

        /*Regex iterators to match each integer in parsed string*/
        auto start = sregex_iterator(row_iter->begin(), row_iter->end(), intRx);
        auto end = sregex_iterator();

        /*Iterates columns. Each string represents a cell's COST in the matrix*/
        for (sregex_iterator cols_iter = start; cols_iter != end; ++cols_iter, ++col_index) {
            string cost_str = cols_iter->str();
            try {
                cost = stoi(cost_str);
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
 template <class P, class S>
P* SearcheableBuilder<P,S>::buildMatrixState(string state_str) {
    regex intRx("(-?\\d+)");
    smatch matches;
    int x, y;

    regex_search(state_str, matches, intRx);
    try {
        x = stoi(matches[1]);
        y = stoi(matches[2]);
    } catch (const char* e) {
        perror("buildMatrixState");
        perror(e);
        return nullptr;
    }
    return new Point(x,y);
}

/** Returns a Vertex which is State<Point>.
 *  NOTE: prev should be nullptr as for now.
 *
 * @param row index
 * @param col index
 * @param cost
 * @param prev should be null ptr
 * @return
 */
 template <class P, class S>
State<P> SearcheableBuilder<P,S>::buildMatrixCell(int row, int col, int cost, Vertex *prev) {
    auto cur_cell = new Point(row, col);
    return Vertex(cur_cell, cost, prev);
}


