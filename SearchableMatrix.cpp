//
// Created by doref on 18/01/2020.
//

#include "SearchableMatrix.h"

/**
 * Returns the initial state
 * @return the initial state
 */
template <class P>
State<P> SearchableMatrix<P>::getInitialState() {
    return (*this->initial_state);
}

/**template<class P>
State<P> SearchableMatrix<P>::getInitialState() {
    return State<P>();
}
 * Check if a certain state is the goal state
 * @param state the state we want to check
 * @return true - if the given state is the goal state, false - otherwises
 */
template <class P>
bool SearchableMatrix<P>::isGoalState(State<P> state) {
    return state == (*goal_state);
}

/**
  * Returns all possible states that you can get to from the given state
  * @param state the state you get from
  * @return a list of all of the the given state neighbors
  */
template <class P>
list<State<P>> SearchableMatrix<P>::getAllPossibleStates(State<P> state) {
    list<State<P>> statesList;

    State<P>* temp = this->getAbove(state);
    if (temp != nullptr) {
        temp->setPrev(state.clone());
        statesList.push_back(*temp);
    }
    temp = this->getBelow(state);
    if (temp != nullptr) {
        temp->setPrev(state.clone());
        statesList.push_back(*temp);
    }
    temp = this->getLeft(state);
    if (temp != nullptr) {
        temp->setPrev(state.clone());
        statesList.push_back(*temp);
    }
    temp = this->getRight(state);
    if (temp != nullptr) {
        temp->setPrev(state.clone());
        statesList.push_back(*temp);
    }
    return statesList;
}

/**
 * Returns the state that's above the given state, if doesn't exists returns null
 * @param curr_state the given state
 * @return the states above the give state, null - if doesn't exist
 *//*
template<class P>
State<P>* SearchableMatrix<P>::getAbove(State<P> curr_state) {
    int upX = curr_state.getState().getX();
    int upY = curr_state.getState().getY() - 1;
    return Matrix<P>::at(upX, upY);
    *//*if (this->isValidCellInMatrix(upX, upY)) {
        return &(this->matrix[upX][upY]);
    }
    return nullptr;*//*
    *//*TODO: When using vector's implmentation...
     *try {
        return this->matrix.at(upX).at(upY);
    } catch (const char *e) {
        return nullptr;
    }*//*
}*/
/*
*//**
 * Returns the state that's below the given state, if doesn't exists returns null
 * @param curr_state the given state
 * @return the states below the give state, null - if doesn't exist
 *//*
template <>
State<Point>* SearchableMatrix<Point>::getBelow(State<Point> curr_state)  {
    int downX = curr_state.getState().getX();
    int downY = curr_state.getState().getY() + 1;
    if (this->isValidCellInMatrix(downX, downY)) {
        return &(this->matrix[downX][downY]);
    }
    return nullptr;
}

*//**
 * Returns the state to the left of the given state, if doesn't exists returns null
 * @param curr_state the given state
 * @return the states that's to the left of the give state, null - if doesn't exist
 *//*
template <>
State<Point>* SearchableMatrix<Point>::getLeft(State<Point> curr_state) {
    int leftX = curr_state.getState().getX() - 1;
    int leftY = curr_state.getState().getY();
    if (this->isValidCellInMatrix(leftX, leftY)) {
        return &(this->matrix[leftX][leftY]);
    }
    return nullptr;
}

*//**
 * Returns the state to the right of the given state, if doesn't exists returns null
 * @param curr_state the given state
 * @return the states that's to the right of the give state, null - if doesn't exist
 *//*
template <>
State<Point>* SearchableMatrix<Point>::getRight(State<Point> curr_state) {
    int rightX = curr_state.getState().getX() + 1;
    int rightY = curr_state.getState().getY();
    if (this->isValidCellInMatrix(rightX, rightY)) {
        return &(this->matrix[rightX][rightY]);
    }
    return nullptr;
}*/

/**
 * Determines if a given coordinates are a valid cell in the matrix
 * @param x the x coordinate
 * @param y the y coordinate
 * @return true - if the coordinate are in the matrix, false - otherwise
 */

/*template <class P>
 * bool SearchableMatrix<P>::isValidCellInMatrix(int x, int y) {
    *//*TODO: why do i see the comparison operatos as overridden?*//*
    if (x >= 0 && x <= this->rows_count - 1) {
        if (y >= 0 && y <= this->columns_count) {
            return true;
        }
    }
    return false;
}*/

/** Adds a row to matrix.
 *
 * @param row vector of Vertices.
 *//*

template <class P>
void SearchableMatrix<P>::addRow(vector<State<P>>* row) {
    Matrix<State<P>>::addRow(row);
}

*/
/** Removes a row given an index.
 *
 * @param row_index
 *//*

template <class P>
void SearchableMatrix<P>::removeRow(int row_index) {
    Matrix<State<P>>::removeRow(row_index);
}
*/

/** Get cell state given state.
 *  NOTE: P is'nt a state, its an inner state of State<P>, (its the P).
 * @param state
 * @return
 */
/*
template <class P>
State<P> *SearchableMatrix<P>::getCell(P *state) {
    for(vector<P> row : this->matrix) {
        if(row.find(*state)) {
            return *(row.find(*state));
        }
    }
    return nullptr;
}

*/
/** Get cell state by given coordinates.
 *
 * @param x
 * @param y
 * @return
 *//*

template <class P>
State<P> *SearchableMatrix<P>::getCell(int x, int y) {
    try {
        return &(this->matrix.at(x).at(y));
    } catch (const char* e) {
        perror("getCell");
        perror(e);
        return nullptr;
    }
}
*/

/** Sets the initial state of the searchable matrix.
 * TODO: Potential bug: initial_state was deleted and then its possible to set it.
 *
 * @param initial_point
 */
template <class P>
void SearchableMatrix<P>::setInitialState(Point initial_point) {
    if(this->initial_state != nullptr) {
        this->initial_state = Matrix<P>::at(initial_point);
    }
}

/** Sets the goal state of the searchable matrix.
 * TODO: Potential bug: initial_state was deleted and then its possible to set it.
 * @param goal_point
 */
template <class P>
void  SearchableMatrix<P>::setGoalState(Point goal_point) {
    if(this->goal_state != nullptr) {
        this->goal_state = Matrix<P>::at(goal_point);
    }
}





