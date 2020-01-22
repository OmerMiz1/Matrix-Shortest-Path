//
// Created by doref on 18/01/2020.
//
#define NOT_A_NODE -1
#include "SearchableMatrix.h"

/**
 * Returns the initial state
 * @return the initial state
 */
template <class P>
P SearchableMatrix<P>::getInitialState() {
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
bool SearchableMatrix<P>::isGoalState(P state) {
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

    P* temp = this->getAbove(state);
    if ((temp != nullptr) && (temp->getCost() != NOT_A_NODE)) {
        temp->setPrev(state.clone());
        statesList.push_back(*temp);
    }
    temp = this->getBelow(state);
    if ((temp != nullptr) && (temp->getCost() != NOT_A_NODE)) {
        temp->setPrev(state.clone());
        statesList.push_back(*temp);
    }
    temp = this->getLeft(state);
    if ((temp != nullptr) && (temp->getCost() != NOT_A_NODE)) {
        temp->setPrev(state.clone());
        statesList.push_back(*temp);
    }
    temp = this->getRight(state);
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
    return *goal_state;
}
