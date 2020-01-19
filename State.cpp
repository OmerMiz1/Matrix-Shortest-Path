//
// Created by omer on 17/01/2020.
//

#include "State.h"

/**
 * A constructor to State
 * @param myState the current state
 * @param cost the cost that it took us to get to this state
 * @param prevState the state that this state got from
 */
template<typename T>
State<T>::State(T *myState, double cost, State<T> *prevState):myState(myState), cost(cost),
                                                                   prev_state(prevState) {}

/**
 * An alternative constructor that gets only the state itself, for use when this state is the first one
 * @param myState the current state
 */
template<typename T>
State<T>::State(T *myState):myState(myState) {
    this->cost = 0;
    this->prev_state = nullptr;
}

/**
 * Returns this states state
 * @return this states state
 */
template<typename T>
T State<T>::getState() {
    return dynamic_cast<Cloneable<T>>(myState)->clone();
}

template <typename T>
double State<T>::getCost() {
    return this->cost;
}

/*template <typename T>
State<T> State<T>::getPrev() {
    return this->prev_state;
}*/

/** Returns true if its the same object.
 *
 * @tparam T
 * @param other_state
 * @return
 */
template <typename T>
bool State<T>::is(State<T> other_state) {
    return (this->cost == other_state.getCost()
    && this->myState == other_state.getState());
    /*TODO: not adding this, might be an expensive recursion*/
}

/**
 * Checks if this state's state equals to other state's state,
 * to be used mostly when checking if a state's state is the goal state
 * @param other_state the other state we want to check with
 * @return true - if their's states are equals, false - otherwise
 */
template<typename T>
bool State<T>::operator==(State<T> other_state) {
    if(ReferenceEquals(this, nullptr) && ReferenceEquals(other_state, nullptr)) {
        return true;
    } else if(ReferenceEquals(this, nullptr) || ReferenceEquals(other_state, nullptr)) {
        return false;
    }
    return (this->cost == other_state.getCost());
}

/**
 * Checks if this state's cost is smaller then an other state's cost
 * @param other_state the other state
 * @return true - if this state's cost is smaller then the other state's cost, false - otherwise
 */
template<typename T>
bool State<T>::operator<(State<T> other_state) {
    return (this->cost < other_state.getCost());
}

template<typename T>
bool State<T>::operator>(State<T> other_state) {
    return (this->cost > other_state.getCost());
}

template<typename T>
void State<T>::setPrev(State<T> prev) {
    this->prev_state = prev;
}

template<class T>
State<T> State<T>::clone() const {
    return State<T>(dynamic_cast<Cloneable<T>>(myState).clone());
}

template<class T>
list<State<T>> State<T>::backtrace() const {
    list<State<T>> backtrace_path;

    for(State<T> cur_front = this->clone(); cur_front != nullptr; cur_front = cur_front.prev_state->clone()) {
        backtrace_path.push_front(cur_front);
    }
    return backtrace_path;
}

/**
 * Update the route to this states //TODO make sure to update priority queue too!
 * @param cost the new cost to get to this state
 * @param prev_state the new prev_state that we got to this state from
 *//*
template<typename T>
void State<T>::updateRoute(double cost, State<T> prev_state) {
    this->cost = cost;
    this->prev_state = prev_state;
}*/
