//
// Created by doref on 18/01/2020.
//

#include "SearchableMatrix.h"

/**
 * Returns the initial state
 * @return the initial state
 */
State<Point> SearchableMatrix::getInitialState() {
    return this->initial_state;
}

/**
 * Check if a certain state is the goal state
 * @param state the state we want to check
 * @return true - if the given state is the goal state, false - otherwises
 */
bool SearchableMatrix::isGoalState(State<Point> state) {
    return state == this->goal_state;
}

 /**
  * Returns all possible states that you can get to from the given state
  * @param state the state you get from
  * @return a list of all of the the given state neighbors
  */
list<State<Point>> SearchableMatrix::getAllPossibleStates(State<Point> state) {
    list<State<Point>> statesList;

    State<Point>* temp = this->getAbove(state);
    if (temp != nullptr) {
        statesList.push_back(*temp);
    }
    temp = this->getBelow(state);
    if (temp != nullptr) {
        statesList.push_back(*temp);
    }
    temp = this->getLeft(state);
    if (temp != nullptr) {
        statesList.push_back(*temp);
    }
    temp = this->getRight(state);
    if (temp != nullptr) {
        statesList.push_back(*temp);
    }
    return statesList;
}

/**
 * Returns the state that's above the given state, if doesn't exists returns null
 * @param curr_state the given state
 * @return the states above the give state, null - if doesn't exist
 */
State<Point> *SearchableMatrix::getAbove(State<Point> curr_state) {
    int upX = curr_state.getState().getX();
    int upY = curr_state.getState().getY() - 1;
    if (this->isValidCellInMatrix(upX, upY)) {
        return &(this->matrix[upX][upY]);
    }
    return nullptr;
}

/**
 * Returns the state that's below the given state, if doesn't exists returns null
 * @param curr_state the given state
 * @return the states below the give state, null - if doesn't exist
 */
State<Point> *SearchableMatrix::getBelow(State<Point> curr_state)  {
    int downX = curr_state.getState().getX();
    int downY = curr_state.getState().getY() + 1;
    if (this->isValidCellInMatrix(downX, downY)) {
        return &(this->matrix[downX][downY]);
    }
    return nullptr;
}

/**
 * Returns the state to the left of the given state, if doesn't exists returns null
 * @param curr_state the given state
 * @return the states that's to the left of the give state, null - if doesn't exist
 */
State<Point> *SearchableMatrix::getLeft(State<Point> curr_state) {
    int leftX = curr_state.getState().getX() - 1;
    int leftY = curr_state.getState().getY();
    if (this->isValidCellInMatrix(leftX, leftY)) {
        return &(this->matrix[leftX][leftY]);
    }
    return nullptr;
}

/**
 * Returns the state to the right of the given state, if doesn't exists returns null
 * @param curr_state the given state
 * @return the states that's to the right of the give state, null - if doesn't exist
 */
State<Point> *SearchableMatrix::getRight(State<Point> curr_state) {
    int rightX = curr_state.getState().getX() + 1;
    int rightY = curr_state.getState().getY();
    if (this->isValidCellInMatrix(rightX, rightY)) {
        return &(this->matrix[rightX][rightY]);
    }
    return nullptr;
}

/**
 * Determines if a given coordinates are a valid cell in the matrix
 * @param x the x coordinate
 * @param y the y coordinate
 * @return true - if the coordinate are in the matrix, false - otherwise
 */
bool SearchableMatrix::isValidCellInMatrix(int x, int y) {
    if (x >= 0 && x <= this->rows_count - 1) {
        if (y >= 0 && y <= this->columns_count) {
            return true;
        }
    }
    return false;
}
