//
// Created by Dor Refaeli on 18/01/2020.
//

#include "SearchableMatrix.h"

template<typename P>
SearchableMatrix<P>::~SearchableMatrix() {
    if(initial_state != nullptr) {
        delete initial_state;
    }
    if(goal_state != nullptr) {
        delete goal_state;
    }
}

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
    return state.getState() == goal_state->getState();
}

/**
  * Returns all possible states that you can get to from the given state
  * @param state the state you get from
  * @return a list of all of the the given state neighbors
  */
template <class P>
list<P> SearchableMatrix<P>::getAllPossibleStates(P state) {
    list<P> statesList;
    auto stateTemp = state.clone();
    /*Explanation:
     * nullptr: if out of bounds.
     * NOT_A_NODE: if cost = -1.
     * If either of the above is true, than not a possible state.*/
    P* temp = Matrix<P>::getAbove(*stateTemp);
    if ((temp != nullptr) && (temp->getCost() != NOT_A_NODE)) {
        temp->setPrev(stateTemp);
        statesList.push_back(*temp);
    }
    temp = Matrix<P>::getBelow(*stateTemp);
    if ((temp != nullptr) && (temp->getCost() != NOT_A_NODE)) {
        temp->setPrev(stateTemp);
        statesList.push_back(*temp);
    }
    temp = Matrix<P>::getLeft(*stateTemp);
    if ((temp != nullptr) && (temp->getCost() != NOT_A_NODE)) {
        temp->setPrev(stateTemp);
        statesList.push_back(*temp);
    }
    temp = Matrix<P>::getRight(*stateTemp);
    if ((temp != nullptr) && (temp->getCost() != NOT_A_NODE)) {
        temp->setPrev(stateTemp);
        statesList.push_back(*temp);
    }

    return statesList;
}

/** Sets the initial state of the searchable matrix.
 * Only allowed once, all other requests will be ignored.
 * @param initial_point_state
 */
template <class P>
void SearchableMatrix<P>::setInitialState(P initial_point_state) {
    initial_state = initial_point_state.clone();
}

/** Sets the goal state of the searchable matrix.
 *
 * @param goal_point_state
 */
template <class P>
void SearchableMatrix<P>::setGoalState(P goal_point_state) {
    goal_state = goal_point_state.clone();

}

/** Returns the goal state.
 *
 * @tparam P
 * @return
 */
template <class P>
P SearchableMatrix<P>::getGoalState() const {
    return *(goal_state->clone());
}

/** Adds a new row to matrix.
 *
 * @tparam P
 * @param new_row
 */
template <typename P>
void SearchableMatrix<P>::addRow(vector<P> *new_row) {
    Matrix<P>::addRow(new_row);
}

/** Removes a row from matrix.
 * Currently not in use, made it for symmetry.
 *
 * @tparam P
 * @param row_num
 */
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
    /*Add state type, initial state and goal state*/
    result.append(typeid(P).name());
    result.append("\n initial: ");
    result.append(initial_state->str());
    result.append("\n goal: ");
    result.append(goal_state->str());
    result.append("\n");

    /*Also add each state (cell)*/
    for(auto &row : Matrix<P>::matrix) {
        for(auto &cell : *row) {
            result.append(to_string(cell->getCost()));
            result.append(",");
            result.append(cell->str());
            result.append(" ");
        }
        /*End of row*/
        result.append("\n");
    }
    return result;
}

