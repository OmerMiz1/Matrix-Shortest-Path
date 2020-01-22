//
// Created by Dor Refaeli on 18/01/2020.
//
#define NOT_A_NODE -1
#include "SearchableMatrix.h"

/**
 * Returns the initial state
 * @return the initial state
 */
template <class P>
P SearchableMatrix<P>::getInitialState()const {
    return *initial_state;
}

/**template<class P>
P SearchableMatrix<P>::getInitialState() {
    return P();
}
 * Check if a certain state is the goal state
 * @param state the state we want to check
 * @return true - if the given state is the goal state, false - otherwises
 */
template <class P>
bool SearchableMatrix<P>::isGoalState(P state)const {
    return state == (*goal_state);
}

/**
  * Returns all possible states that you can get to from the given state
  * @param state the state you get from
  * @return a list of all of the the given state neighbors
  */
template <class P>
list<P> SearchableMatrix<P>::getAllPossibleStates(P state) {
    list<P> statesList;

    P* temp = Matrix<P>::getAbove(state);
    if ((temp != nullptr) && (temp->getCost() != NOT_A_NODE)) {
        temp->setPrev(state.clone());
        statesList.push_back(*temp);
    }

    temp = Matrix<P>::getBelow(state);
    if ((temp != nullptr) && (temp->getCost() != NOT_A_NODE)) {
        temp->setPrev(state.clone());
        statesList.push_back(*temp);
    }
    temp = Matrix<P>::getLeft(state);
    if ((temp != nullptr) && (temp->getCost() != NOT_A_NODE)) {
        temp->setPrev(state.clone());
        statesList.push_back(*temp);
    }
    temp = Matrix<P>::getRight(state);
    if ((temp != nullptr) && (temp->getCost() != NOT_A_NODE)) {
        temp->setPrev(state.clone());
        statesList.push_back(*temp);
    }
    return statesList;
}

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

template <class P>
P SearchableMatrix<P>::getGoalState() const {
    return *(goal_state->clone());
}

template <typename P>
void SearchableMatrix<P>::addRow(vector<P> *new_row) {
    Matrix<P>::addRow(new_row);
}

template<typename P>
void SearchableMatrix<P>::removeRow(int row_num) {
    Matrix<P>::removeRow(row_num);
}

/** Returns a string description of the matrix.
 *
 * @tparam P
 * @return
 */
template<typename P>
string SearchableMatrix<P>::str() const {
    string result;
    /*Add typename, initial state and goal state*/

    result = typeid(this).name();
    result.append("\n initial: ");
    result.append(initial_state->str());
    result.append("\n goal: ");
    result.append(goal_state->str());
    result.append("\n");

    /*Also add each cell*/
    for(auto &row : Matrix<P>::matrix) {
        for(auto &cell : row) {
            result.append(cell.str());
            result.append(" ");
        }
        /*End of row*/
        result.append("\n");
    }
    return result;
}

